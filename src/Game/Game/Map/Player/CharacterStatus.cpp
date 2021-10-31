#include"../header/CharacterStatus.h"
#include"../header/Function.h"
#include"../header/EnemyStatus.h"
#include"../header/CharacterSkillInfoList.h"
#include"../header/ItemInfoList.h"
#include"../header/EnemyStatus.h"
#include"../header/KeyBoard.h"
#include"../header/EnemySkillInfoList.h"
#include"../header/BattleEffectP000.h"

string CharacterStatus::nameList[Define::CHARACTER_NUM];
int CharacterStatus::defaultLv[Define::CHARACTER_NUM];
int CharacterStatus::BaseHP[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
int CharacterStatus::BaseSP[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
int CharacterStatus::BaseATK[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
int CharacterStatus::BaseDEF[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
int CharacterStatus::BaseINT[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
int CharacterStatus::BaseRES[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
int CharacterStatus::NeedEXP[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
array<array<vector<int>, Define::MAX_LEVEL + 1>, Define::CHARACTER_NUM> CharacterStatus::LearnSkill;
array<vector<int>, Define::CHARACTER_NUM> CharacterStatus::CanEquipWeapon;
array<vector<int>, Define::CHARACTER_NUM> CharacterStatus::CanEquipHead;
array<vector<int>, Define::CHARACTER_NUM> CharacterStatus::CanEquipChest;
array<vector<int>, Define::CHARACTER_NUM> CharacterStatus::CanEquipAccessory;
int CharacterStatus::defaultSetSkill[Define::CHARACTER_NUM][3];

CharacterStatus::CharacterStatus(int characterNum, array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int loadDataNum) :characterNum(characterNum)
{
	Lv = defaultLv[characterNum];

	if (loadDataNum != -1)
	{
		Lv = saveDataList[loadDataNum].Lv[characterNum];
	}

	name = nameList[characterNum];
	HP = BaseHP[characterNum][Lv];
	MAX_HP = BaseHP[characterNum][Lv];
	SP = BaseSP[characterNum][Lv];
	MAX_SP = BaseSP[characterNum][Lv];
	ATK = BaseATK[characterNum][Lv];
	DEF = BaseDEF[characterNum][Lv];
	INT = BaseINT[characterNum][Lv];
	RES = BaseRES[characterNum][Lv];
	EXP = 0;
	weapon = -1;
	head = -1;
	chest = -1;
	accessory[0] = -1;
	accessory[1] = -1;
	accessory[2] = -1;
	setSkill[0] = defaultSetSkill[characterNum][0];
	setSkill[1] = defaultSetSkill[characterNum][1];
	setSkill[2] = defaultSetSkill[characterNum][2];
	canEquipWeapon = CanEquipWeapon[characterNum];
	canEquipHead = CanEquipHead[characterNum];
	canEquipChest = CanEquipChest[characterNum];
	canEquipAccessory = CanEquipAccessory[characterNum];

	for (int i = 0; i < (int)ConditionError::SIZE; i++)
	{
		conditionError[i] = false;
		conditionErrorTimer[i] = 0;
	}

	for (int i = 0; i < Lv + 1; i++)
	{
		for (auto& num : LearnSkill[characterNum][i])
		{
			if (num != -1)
			{
				learnSkillList.push_back(num);
			}
		}
	}

	for (int i = 0; i < Define::PLAYER_SKILL_MAX; i++)
	{
		if (i < CharacterSkillInfoList::GetCharacterSkillInfoList().size())
		{
			skillLevel[i] = CharacterSkillInfoList::GetCharacterSkillInfoList()[i].defaultLevel;
		}
		else
		{
			skillLevel[i] = 1;
		}
		skillEXP[i] = 0;
	}

	for (int i = 0; i != ATKMagnification.size(); i++)
	{
		ATKMagnification[i] = 1.0;
		INTMagnification[i] = 1.0;
		DEFMagnification[i] = 1.0;
		RESMagnification[i] = 1.0;
		ATKMagnificationTimer[i] = 0;
		INTMagnificationTimer[i] = 0;
		DEFMagnificationTimer[i] = 0;
		RESMagnificationTimer[i] = 0;
	}
	reduceSPUse = 0;
	reduceStiff = 0;
	reduceSPUseTimer = 0;
	reduceStiffTimer = 0;
	autoHeelHPAmount = 0;
	autoHeelSPAmount = 0;
	autoHeelTimer = 0;
	normalMagnification = 1.0;
	skillMagnification = 1.0;

	if (loadDataNum != -1)
	{
		HP = saveDataList[loadDataNum].HP[characterNum];
		SP = saveDataList[loadDataNum].SP[characterNum];
		EXP = saveDataList[loadDataNum].EXP[characterNum];
		weapon = saveDataList[loadDataNum].weapon[characterNum];
		head = saveDataList[loadDataNum].head[characterNum];
		chest = saveDataList[loadDataNum].chest[characterNum];
		for (int i = 0; i < 3; i++)
		{
			accessory[i] = saveDataList[loadDataNum].accessory[characterNum][i];
			setSkill[i] = saveDataList[loadDataNum].setSkill[characterNum][i];
		}
		for (int i = 0; i < Define::PLAYER_SKILL_MAX; i++)
		{
			skillLevel[i] = saveDataList[loadDataNum].skillLevel[characterNum][i];
			skillEXP[i] = saveDataList[loadDataNum].skillEXP[characterNum][i];
		}
		UpdateStatus(false);
	}
}

CharacterStatus::~CharacterStatus()
{

}

void CharacterStatus::Load()
{
	ifstream ifs;

	ifs.open("data/csv/character/characterStatus.csv");

	assert(!ifs.fail() && "CharacterStatus::Load()");

	string readString;

	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		getline(ifs, readString);

		{
			auto element = Function::split(readString, ',');
			assert(element[0] != "" && "CharacterStatusLoad() サイズが不正です。");
			stringstream ss;
			ss << element[0];
			ss >> nameList[i];
		}

		getline(ifs, readString);

		{
			auto element = Function::split(readString, ',');
			assert(element[0] != "" && "CharacterStatusLoad() サイズが不正です。");
			stringstream ss;
			ss << element[0];
			ss >> defaultLv[i];
		}

		getline(ifs, readString);

		{
			auto element = Function::split(readString, ',');
			assert(element[0] != "" && "CharacterStatusLoad() サイズが不正です。");
			for (int j = 0; j < 3; j++)
			{
				stringstream ss;
				ss << element[j];
				ss >> defaultSetSkill[i][j];
			}
		}

		for (int j = 0; j < Define::MAX_LEVEL + 1; j++)
		{
			getline(ifs, readString);
			auto element = Function::split(readString, ',');
			assert(element.size() == 8 && "CharacterStatusLoad() サイズが不正です。");

			for (int k = 0; k != element.size(); k++)
			{
				stringstream ss;
				ss << element[k];
				switch (k)
				{
				case 0:
					ss >> BaseHP[i][j];
					break;
				case 1:
					ss >> BaseSP[i][j];
					break;
				case 2:
					ss >> BaseATK[i][j];
					break;
				case 3:
					ss >> BaseDEF[i][j];
					break;
				case 4:
					ss >> BaseINT[i][j];
					break;
				case 5:
					ss >> BaseRES[i][j];
					break;
				case 6:
					ss >> NeedEXP[i][j];
					break;
				case 7:
				{
					auto element2 = Function::split(element[k], '|');
					for (int l = 0; l != element2.size(); l++)
					{
						stringstream ss2;
						int num;
						ss2 << element2[l];
						ss2 >> num;
						LearnSkill[i][j].push_back(num);
					}
				}
					break;
				}
			}
		}
		getline(ifs, readString);

		{
			auto element = Function::split(readString, ',');

			for (int k = 0; k != element.size(); k++)
			{
				auto element2 = Function::split(element[k], '|');

				switch (k)
				{
				case 0:
					for (auto& n : element2)
					{
						stringstream ss;
						int num;
						ss << n;
						ss >> num;
						CanEquipWeapon[i].push_back(num);
					}
					break;
				case 1:
					for (auto& n : element2)
					{
						stringstream ss;
						int num;
						ss << n;
						ss >> num;
						CanEquipHead[i].push_back(num);
					}
					break;
				case 2:
					for (auto& n : element2)
					{
						stringstream ss;
						int num;
						ss << n;
						ss >> num;
						CanEquipChest[i].push_back(num);
					}
					break;
				case 3:
					for (auto& n : element2)
					{
						stringstream ss;
						int num;
						ss << n;
						ss >> num;
						CanEquipAccessory[i].push_back(num);
					}
					break;
				}
			}
		}

		getline(ifs, readString);
	}
	
	ifs.close();
}

void CharacterStatus::UpdateMap()
{
	UpdateMagnification();
	UpdateAutoHeel();
}

void CharacterStatus::UpdateAutoHeel()
{
	if (autoHeelTimer%autoHeelInterval == 0)
	{
		HP += (int)autoHeelHPAmount;
		HP = max(0, min(MAX_HP, HP));
		SP += (int)autoHeelSPAmount;
		SP = max(0, min(MAX_SP, SP));
	}
	autoHeelTimer++;
}

void CharacterStatus::UpdateMagnification()
{
	for (int i = 0; i != ATKMagnification.size(); i++)
	{
		if (ATKMagnificationTimer[i] > 0)
		{
			ATKMagnificationTimer[i]--;
			if (ATKMagnificationTimer[i] == 0)
			{
				ATKMagnification[i] = 1.0;
			}
		}
		if (INTMagnificationTimer[i] > 0)
		{
			INTMagnificationTimer[i]--;
			if (INTMagnificationTimer[i] == 0)
			{
				INTMagnification[i] = 1.0;
			}
		}
		if (DEFMagnificationTimer[i] > 0)
		{
			DEFMagnificationTimer[i]--;
			if (DEFMagnificationTimer[i] == 0)
			{
				DEFMagnification[i] = 1.0;
			}
		}
		if (RESMagnificationTimer[i] > 0)
		{
			RESMagnificationTimer[i]--;
			if (RESMagnificationTimer[i] == 0)
			{
				RESMagnification[i] = 1.0;
			}
		}
	}
	if (reduceSPUseTimer > 0)
	{
		reduceSPUseTimer--;
		if (reduceSPUseTimer == 0)
		{
			reduceSPUse = 0;
		}
	}
	if (reduceStiffTimer > 0)
	{
		reduceStiffTimer--;
		if (reduceStiffTimer == 0)
		{
			reduceStiff = 0;
		}
	}
}

void CharacterStatus::UpdateConditionError()
{
	if (HP != 0)
	{
		if (conditionError[(int)ConditionError::POISON])
		{
			if (conditionErrorTimer[(int)ConditionError::POISON] % Define::POISON_DAMAGE_INTERVAL == 1)
			{
				HP -= MAX_HP*Define::POISON_DAMAGE_RATE;
				HP = max(1, HP);
			}
		}
	}
}

void CharacterStatus::UpdateConditionErrorTimer()
{
	for (int i = 0; i < (int)ConditionError::SIZE; i++)
	{
		if (conditionErrorTimer[i] > 0)
		{
			conditionErrorTimer[i]--;
			if (conditionErrorTimer[i] == 0)
			{
				conditionError[i] = false;
			}
		}
	}
}

void CharacterStatus::UpdateStatus(bool LvUp)
{
	if (LvUp)
	{
		HP += BaseHP[characterNum][Lv] - BaseHP[characterNum][Lv - 1];
		SP += BaseSP[characterNum][Lv] - BaseSP[characterNum][Lv - 1];
	}

	MAX_HP = BaseHP[characterNum][Lv];
	MAX_SP = BaseSP[characterNum][Lv];
	ATK = BaseATK[characterNum][Lv];
	DEF = BaseDEF[characterNum][Lv];
	INT = BaseINT[characterNum][Lv];
	RES = BaseRES[characterNum][Lv];

	autoHeelHPAmount = 0;
	autoHeelSPAmount = 0;
	normalMagnification = 1.0;
	skillMagnification = 1.0;

	if (weapon != -1)
	{
		MAX_HP += ItemInfoList::GetItemInfoList()[weapon].HP;
		MAX_SP += ItemInfoList::GetItemInfoList()[weapon].SP;
		ATK += ItemInfoList::GetItemInfoList()[weapon].ATK;
		DEF += ItemInfoList::GetItemInfoList()[weapon].DEF;
		INT += ItemInfoList::GetItemInfoList()[weapon].INT;
		RES += ItemInfoList::GetItemInfoList()[weapon].RES;

		autoHeelHPAmount += ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::AUTO_HEEL_HP_AMOUNT];
		autoHeelSPAmount += ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::AUTO_HEEL_MP_AMOUNT];
		if (ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT] > 0.001)
		{
			normalMagnification *= ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT];
		}
		if (ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT] > 0.001)
		{
			skillMagnification *= ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT];
		}
	}

	if (head != -1)
	{
		MAX_HP += ItemInfoList::GetItemInfoList()[head].HP;
		MAX_SP += ItemInfoList::GetItemInfoList()[head].SP;
		ATK += ItemInfoList::GetItemInfoList()[head].ATK;
		DEF += ItemInfoList::GetItemInfoList()[head].DEF;
		INT += ItemInfoList::GetItemInfoList()[head].INT;
		RES += ItemInfoList::GetItemInfoList()[head].RES;

		autoHeelHPAmount += ItemInfoList::GetItemInfoList()[head].option[(int)ItemInfo::ItemOption::AUTO_HEEL_HP_AMOUNT];
		autoHeelSPAmount += ItemInfoList::GetItemInfoList()[head].option[(int)ItemInfo::ItemOption::AUTO_HEEL_MP_AMOUNT];
		if (ItemInfoList::GetItemInfoList()[head].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT] > 0.001)
		{
			normalMagnification *= ItemInfoList::GetItemInfoList()[head].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT];
		}
		if (ItemInfoList::GetItemInfoList()[head].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT] > 0.001)
		{
			skillMagnification *= ItemInfoList::GetItemInfoList()[head].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT];
		}
	}

	if (chest != -1)
	{
		MAX_HP += ItemInfoList::GetItemInfoList()[chest].HP;
		MAX_SP += ItemInfoList::GetItemInfoList()[chest].SP;
		ATK += ItemInfoList::GetItemInfoList()[chest].ATK;
		DEF += ItemInfoList::GetItemInfoList()[chest].DEF;
		INT += ItemInfoList::GetItemInfoList()[chest].INT;
		RES += ItemInfoList::GetItemInfoList()[chest].RES;

		autoHeelHPAmount += ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::AUTO_HEEL_HP_AMOUNT];
		autoHeelSPAmount += ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::AUTO_HEEL_MP_AMOUNT];
		if (ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT] > 0.001)
		{
			normalMagnification *= ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT];
		}
		if (ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT] > 0.001)
		{
			skillMagnification *= ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT];
		}
	}

	if (accessory[0] != -1)
	{
		MAX_HP += ItemInfoList::GetItemInfoList()[accessory[0]].HP;
		MAX_SP += ItemInfoList::GetItemInfoList()[accessory[0]].SP;
		ATK += ItemInfoList::GetItemInfoList()[accessory[0]].ATK;
		DEF += ItemInfoList::GetItemInfoList()[accessory[0]].DEF;
		INT += ItemInfoList::GetItemInfoList()[accessory[0]].INT;
		RES += ItemInfoList::GetItemInfoList()[accessory[0]].RES;

		autoHeelHPAmount += ItemInfoList::GetItemInfoList()[accessory[0]].option[(int)ItemInfo::ItemOption::AUTO_HEEL_HP_AMOUNT];
		autoHeelSPAmount += ItemInfoList::GetItemInfoList()[accessory[0]].option[(int)ItemInfo::ItemOption::AUTO_HEEL_MP_AMOUNT];
		if (ItemInfoList::GetItemInfoList()[accessory[0]].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT] > 0.001)
		{
			normalMagnification *= ItemInfoList::GetItemInfoList()[accessory[0]].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT];
		}
		if (ItemInfoList::GetItemInfoList()[accessory[0]].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT] > 0.001)
		{
			skillMagnification *= ItemInfoList::GetItemInfoList()[accessory[0]].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT];
		}
	}

	if (accessory[1] != -1)
	{
		MAX_HP += ItemInfoList::GetItemInfoList()[accessory[1]].HP;
		MAX_SP += ItemInfoList::GetItemInfoList()[accessory[1]].SP;
		ATK += ItemInfoList::GetItemInfoList()[accessory[1]].ATK;
		DEF += ItemInfoList::GetItemInfoList()[accessory[1]].DEF;
		INT += ItemInfoList::GetItemInfoList()[accessory[1]].INT;
		RES += ItemInfoList::GetItemInfoList()[accessory[1]].RES;

		autoHeelHPAmount += ItemInfoList::GetItemInfoList()[accessory[1]].option[(int)ItemInfo::ItemOption::AUTO_HEEL_HP_AMOUNT];
		autoHeelSPAmount += ItemInfoList::GetItemInfoList()[accessory[1]].option[(int)ItemInfo::ItemOption::AUTO_HEEL_MP_AMOUNT];
		if (ItemInfoList::GetItemInfoList()[accessory[1]].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT] > 0.001)
		{
			normalMagnification *= ItemInfoList::GetItemInfoList()[accessory[1]].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT];
		}
		if (ItemInfoList::GetItemInfoList()[accessory[1]].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT] > 0.001)
		{
			skillMagnification *= ItemInfoList::GetItemInfoList()[accessory[1]].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT];
		}
	}

	if (accessory[2] != -1)
	{
		MAX_HP += ItemInfoList::GetItemInfoList()[accessory[2]].HP;
		MAX_SP += ItemInfoList::GetItemInfoList()[accessory[2]].SP;
		ATK += ItemInfoList::GetItemInfoList()[accessory[2]].ATK;
		DEF += ItemInfoList::GetItemInfoList()[accessory[2]].DEF;
		INT += ItemInfoList::GetItemInfoList()[accessory[2]].INT;
		RES += ItemInfoList::GetItemInfoList()[accessory[2]].RES;

		autoHeelHPAmount += ItemInfoList::GetItemInfoList()[accessory[2]].option[(int)ItemInfo::ItemOption::AUTO_HEEL_HP_AMOUNT];
		autoHeelSPAmount += ItemInfoList::GetItemInfoList()[accessory[2]].option[(int)ItemInfo::ItemOption::AUTO_HEEL_MP_AMOUNT];
		if (ItemInfoList::GetItemInfoList()[accessory[2]].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT] > 0.001)
		{
			normalMagnification *= ItemInfoList::GetItemInfoList()[accessory[2]].option[(int)ItemInfo::ItemOption::RAISE_NORMAL_ATTACK_DAMAGE_PERCENT];
		}
		if (ItemInfoList::GetItemInfoList()[accessory[2]].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT] > 0.001)
		{
			skillMagnification *= ItemInfoList::GetItemInfoList()[accessory[2]].option[(int)ItemInfo::ItemOption::RAISE_SKILL_DAMAGE_PERCENT];
		}
	}
}

void CharacterStatus::AddSkill()
{
	for (auto& num : LearnSkill[characterNum][Lv])
	{
		if (num != -1)
		{
			learnSkillList.push_back(num);
		}
	}
}

void CharacterStatus::AddEXP(int value)
{
	if (HP == 0||Lv==Define::MAX_LEVEL)
	{
		return;
	}
	EXP += value;
	if (EXP >= NeedEXP[characterNum][Lv])
	{
		int overEXP = EXP - NeedEXP[characterNum][Lv];
		EXP = 0;
		Lv++;
		AddSkill();
		UpdateStatus(true);
		AddEXP(overEXP);
	}
}

void CharacterStatus::Damage(int damage)
{
	HP -= damage;
	HP = max(0, HP);
}

void CharacterStatus::UseItem(int itemKind)
{
	auto info = ItemInfoList::GetItemInfoList()[itemKind];

	if (info.option[(int)ItemInfo::ItemOption::HP_HEAL_VALUE]>0.001)
	{
		HP += (int)info.option[(int)ItemInfo::ItemOption::HP_HEAL_VALUE];
		HP = min(MAX_HP, HP);
	}
	if (info.option[(int)ItemInfo::ItemOption::MP_HEAL_VALUE]>0.001)
	{
		SP += (int)info.option[(int)ItemInfo::ItemOption::MP_HEAL_VALUE];
		SP = min(MAX_SP, SP);
	}
	if (info.option[(int)ItemInfo::ItemOption::CURE_ALL_CONDITIONERROR ] > 0.001)
	{
		fill(conditionError.begin(), conditionError.end(), false);
		fill(conditionErrorTimer.begin(), conditionErrorTimer.end(), 0);
	}
	if (info.option[(int)ItemInfo::ItemOption::REVIVAL] > 0.001)
	{
		HP = MAX_HP;
	}
	if (info.option[(int)ItemInfo::ItemOption::HEAL_MAX]>0.001)
	{
		HP = MAX_HP;
		SP = MAX_SP;
	}

	if (info.option[(int)ItemInfo::ItemOption::ATK_UP_PERCENT] > 0.001)
	{
		ATKMagnification[0] = info.option[(int)ItemInfo::ItemOption::ATK_UP_PERCENT];
		ATKMagnificationTimer[0] = info.option[(int)ItemInfo::ItemOption::ATK_UP_TIME];
	}
	if (info.option[(int)ItemInfo::ItemOption::INT_UP_PERCENT] > 0.001)
	{
		INTMagnification[0] = info.option[(int)ItemInfo::ItemOption::INT_UP_PERCENT];
		INTMagnificationTimer[0] = info.option[(int)ItemInfo::ItemOption::INT_UP_TIME];
	}
	if (info.option[(int)ItemInfo::ItemOption::DEF_UP_PERCENT] > 0.001)
	{
		DEFMagnification[0] = info.option[(int)ItemInfo::ItemOption::DEF_UP_PERCENT];
		DEFMagnificationTimer[0] = info.option[(int)ItemInfo::ItemOption::DEF_UP_TIME];
	}
	if (info.option[(int)ItemInfo::ItemOption::RES_UP_PERCENT] > 0.001)
	{
		RESMagnification[0] = info.option[(int)ItemInfo::ItemOption::RES_UP_PERCENT];
		RESMagnificationTimer[0] = info.option[(int)ItemInfo::ItemOption::RES_UP_TIME];
	}
	if (info.option[(int)ItemInfo::ItemOption::REDUCE_STIFF_AMOUNT] > 0.001)
	{
		reduceStiff = info.option[(int)ItemInfo::ItemOption::REDUCE_STIFF_AMOUNT];
		reduceStiffTimer = info.option[(int)ItemInfo::ItemOption::REDUCE_STIFF_TIME];
	}
	if (info.option[(int)ItemInfo::ItemOption::REDUCE_PAY_MP_AMOUNT] > 0.001)
	{
		reduceSPUse = info.option[(int)ItemInfo::ItemOption::REDUCE_PAY_MP_AMOUNT];
		reduceSPUseTimer = info.option[(int)ItemInfo::ItemOption::REDUCE_PAY_MP_TIME];
	}
}

void CharacterStatus::CauseSkill(int skillKind)
{
	switch (skillKind)
	{
	case 18:
		HP = MAX_HP;
		break;
	case 19:
		fill(conditionError.begin(), conditionError.end(), false);
		fill(conditionErrorTimer.begin(), conditionErrorTimer.end(), 0);
		break;
	case 20:
		DEFMagnification[1] = CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].value[0];
		DEFMagnificationTimer[1] = CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].stiff[0];
		RESMagnification[1] = CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].value[0];
		RESMagnificationTimer[1] = CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].stiff[0];
		break;
	case 22:
		ATKMagnification[1] = CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].value[0];
		ATKMagnificationTimer[1] = CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].stiff[0];
		INTMagnification[1] = CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].value[0];
		INTMagnificationTimer[1] = CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].stiff[0];
		break;
	}
}

void CharacterStatus::PaySP(int skillKind)
{
	int paySP = CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].paySP[skillLevel[skillKind] - 1];
	if (skillKind == 18)
	{
		paySP = MAX_SP / 2;
	}
	paySP -= reduceSPUse;
	paySP = max(0, paySP);

	if (weapon!=-1&&ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::REDUCE_PAY_MP_PERCENT] > 0.001)
	{
		paySP *= ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::REDUCE_PAY_MP_PERCENT];
	}

	SP -= paySP;
	assert(SP >= 0 && "CharacterStatus::PaySP()");

	AddSkillEXP(skillKind);
}

void CharacterStatus::AddSkillEXP(int skillKind)
{
	if (skillLevel[skillKind] < Define::PLAYER_SKILL_LEVEL_MAX)
	{
		skillEXP[skillKind]++;
		if (skillEXP[skillKind] == CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].needPoint[skillLevel[skillKind] - 1])
		{
			skillEXP[skillKind] = 0;
			skillLevel[skillKind]++;
		}
	}
}

void CharacterStatus::SetSkill(int i, int skillKind)
{
	for (int j = 0; j < 3; j++)
	{
		if (setSkill[j] == skillKind)
		{
			setSkill[j] = -1;
		}
	}
	setSkill[i] = skillKind;
}

void CharacterStatus::SetWeapon(int itemKind)
{
	weapon = itemKind; 
	UpdateStatus(false);
}

void CharacterStatus::RemoveWeapon()
{
	weapon = -1;
	UpdateStatus(false);
}

void CharacterStatus::SetHead(int itemKind)
{
	head = itemKind; 
	UpdateStatus(false);
}

void CharacterStatus::RemoveHead()
{
	head = -1;
	UpdateStatus(false);
}

void CharacterStatus::SetChest(int itemKind) 
{
	chest = itemKind; 
	UpdateStatus(false);
}

void CharacterStatus::RemoveChest()
{
	chest = -1;
	UpdateStatus(false);
}

void CharacterStatus::SetAccessory(int i, int itemKind) 
{
	accessory[i] = itemKind; 
	UpdateStatus(false);
}

void CharacterStatus::RemoveAccessory(int num)
{
	accessory[num] = -1;
	UpdateStatus(false);
}

void CharacterStatus::UseINN()
{
	HP = MAX_HP;
	SP = MAX_SP;
}

void CharacterStatus::Hit(int value, int skillNum)
{
	if (HP == 0)
	{
		return;
	}
	double drainPercent = 0.0;
	for (auto n : accessory)
	{
		if (n != -1)
		{
			if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::HEEL_HP_WHEN_ATTACK] > 0.001)
			{
				drainPercent += ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::HEEL_HP_WHEN_ATTACK];
			}
		}
	}

	HP += value*drainPercent;
	HP = min(MAX_HP, HP);

	int SPPlus = 0;

	for (auto n : accessory)
	{
		if (n != -1)
		{
			if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::HEEL_MP_WHEN_ATTACK] > 0.001)
			{
				SPPlus += ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::HEEL_MP_WHEN_ATTACK];
			}
		}
	}

	if (skillNum == 100)
	{
		SP += (Define::HEEL_SP_ATTACK100 + SPPlus);
		SP = min(MAX_SP, SP);
	}
	if (skillNum == 101)
	{
		SP += (Define::HEEL_SP_ATTACK101 + SPPlus);
		SP = min(MAX_SP, SP);
	}
}

int CharacterStatus::CauseByEnemy(EnemyStatus enemyStatus, int sourceID, int skillKind,bool stiffFlag,bool guardFlag,int guardCounter)
{
	int value = 0;
	bool endureFlag = HP >= (MAX_HP / 2) && chest != -1 && ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::HALF_DEFENCE];

	if (EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].attribute[(int)EnemySkillAttribute::TYPE] == 0)
	{
		value += (enemyStatus.GetATK() * 4- GetDEF() * 2);
	}
	else
	{
		value += (enemyStatus.GetINT() * 4 - GetRES() * 2);
	}
	value *= EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].value;

	value = value - value*0.1 + value*0.2*((GetRand(10000) % 100) / 100.0);

	if (stiffFlag)
	{
		for (auto n : accessory)
		{
			if (n != -1)
			{
				if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::REDUCE_DAMAGE_WHEN_STIFFING_PERCENT] > 0.001)
				{
					value *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::REDUCE_DAMAGE_WHEN_STIFFING_PERCENT];
				}
			}
		}
	}

	if (guardFlag)
	{
		if (guardCounter > Define::JUST_GUARD_TIME)
		{
			if (SP >= (int)(Define::NEED_GUARD_SP*MAX_SP))
			{
				value *= Define::GUARD_REDUCE_RATE;
				SP -= (int)(Define::NEED_GUARD_SP*MAX_SP);
			}
		}
	}

	if (EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].attribute[(int)EnemySkillAttribute::TYPE] == 0)
	{
		value = max(enemyStatus.GetATK() / 2, value);
	}
	else
	{
		value = max(enemyStatus.GetINT() / 2, value);
	}

	if (guardFlag)
	{
		if (guardCounter <= Define::JUST_GUARD_TIME)
		{
			value = 0;
		}
	}
	HP -= value;

	HP = max(min(HP, MAX_HP), endureFlag ? 1 : 0);

	if (value > 0)
	{
		conditionError[(int)ConditionError::SLEEP] = false;
		conditionErrorTimer[(int)ConditionError::SLEEP] = 0;
	}

	bool preventCondition[3] = { false };
	
	if ((chest!=-1&&ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::PREVENT_POISON] > 0.001) || find_if(accessory.begin(), accessory.end(), [](int n) {return (n!=-1&&ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::PREVENT_POISON] > 0.001); }) != accessory.end())
	{
		preventCondition[(int)ConditionError::POISON] = true;
	}
	if ((chest!=-1&&ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::PREVENT_SLEEPING] > 0.001) || find_if(accessory.begin(), accessory.end(), [](int n) {return (n!=-1&&ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::PREVENT_SLEEPING] > 0.001); }) != accessory.end())
	{
		preventCondition[(int)ConditionError::SLEEP] = true;
	}
	if ((chest!=-1&&ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::PREVENT_STAN] > 0.001) || find_if(accessory.begin(), accessory.end(), [](int n) {return (n!=-1&&ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::PREVENT_STAN] > 0.001); }) != accessory.end())
	{
		preventCondition[(int)ConditionError::STAN] = true;
	}

	if (!preventCondition[0])
	{
		int randNum = GetRand(10000) % 100;
		if (randNum < EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].attribute[1])
		{
			conditionError[0] = true;
			conditionErrorTimer[0] = Define::POISON_TIME;
		}
	}
	if (!preventCondition[1])
	{
		int randNum = GetRand(10000) % 100;
		if (randNum < EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].attribute[2])
		{
			conditionError[1] = true;
			conditionErrorTimer[1] = Define::SLEEP_TIME;
		}
	}
	if (!preventCondition[2])
	{
		int randNum = GetRand(10000) % 100;
		if (randNum < EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].attribute[3])
		{
			conditionError[2] = true;
			conditionErrorTimer[2] = Define::STAN_TIME;
		}
	}

	return value;
}

int CharacterStatus::CauseByBoss(BossStatus bossStatus, int sourceID, int skillKind,bool stiffFlag,bool guardFlag,int guardCounter)
{
	int value = 0;
	bool endureFlag = HP >= (MAX_HP / 2) && chest != -1 && ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::HALF_DEFENCE];

	if (EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].attribute[(int)EnemySkillAttribute::TYPE] == 0)
	{
		value += (bossStatus.GetATK() * 4 - GetDEF() * 2);
	}
	else
	{
		value += (bossStatus.GetINT() * 4- GetRES() * 2);
	}
	value *= EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].value;

	value = value - value*0.1 + value*0.2*((GetRand(10000) % 100) / 100.0);

	if (stiffFlag)
	{
		for (auto n : accessory)
		{
			if (n != -1)
			{
				if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::REDUCE_DAMAGE_WHEN_STIFFING_PERCENT] > 0.001)
				{
					value *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::REDUCE_DAMAGE_WHEN_STIFFING_PERCENT];
				}
			}
		}
	}

	if (guardFlag)
	{
		if (guardCounter > Define::JUST_GUARD_TIME)
		{
			if (SP >= (int)(Define::NEED_GUARD_SP*MAX_SP))
			{
				value *= Define::GUARD_REDUCE_RATE;
				SP -= (int)(Define::NEED_GUARD_SP*MAX_SP);
			}
		}
	}

	if (EnemySkillInfoList::GetEnemySkillInfoList()[skillKind].attribute[(int)EnemySkillAttribute::TYPE] == 0)
	{
		value = max(bossStatus.GetATK() / 2, value);
	}
	else
	{
		value = max(bossStatus.GetINT() / 2, value);
	}

	if (guardFlag)
	{
		if (guardCounter <= Define::JUST_GUARD_TIME)
		{
			value = 0;
		}
	}

	HP -= value;

	HP = max(min(HP, MAX_HP), endureFlag ? 1 : 0);

	if (value > 0)
	{
		conditionError[(int)ConditionError::SLEEP] = false;
		conditionErrorTimer[(int)ConditionError::SLEEP] = 0;
	}

	bool preventCondition[3] = { false };

	if ((chest != -1 && ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::PREVENT_POISON > 0.001]) || find_if(accessory.begin(), accessory.end(), [](int n) {return (n != -1 && ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::PREVENT_POISON] > 0.001); }) != accessory.end())
	{
		preventCondition[(int)ConditionError::POISON] = true;
	}
	if ((chest != -1 && ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::PREVENT_SLEEPING > 0.001]) || find_if(accessory.begin(), accessory.end(), [](int n) {return (n != -1 && ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::PREVENT_SLEEPING] > 0.001); }) != accessory.end())
	{
		preventCondition[(int)ConditionError::SLEEP] = true;
	}
	if ((chest != -1 && ItemInfoList::GetItemInfoList()[chest].option[(int)ItemInfo::ItemOption::PREVENT_STAN > 0.001]) || find_if(accessory.begin(), accessory.end(), [](int n) {return (n != -1 && ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::PREVENT_STAN] > 0.001); }) != accessory.end())
	{
		preventCondition[(int)ConditionError::STAN] = true;
	}

	return value;
}

void CharacterStatus::Save(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int saveDataNum)
{
	saveDataList[saveDataNum].Lv[characterNum] = Lv;
	saveDataList[saveDataNum].HP[characterNum] = HP;
	saveDataList[saveDataNum].SP[characterNum] = SP;
	saveDataList[saveDataNum].EXP[characterNum] = EXP;
	saveDataList[saveDataNum].weapon[characterNum] = weapon;
	saveDataList[saveDataNum].head[characterNum] = head;
	saveDataList[saveDataNum].chest[characterNum] = chest;

	for (int i = 0; i < 3; i++)
	{
		saveDataList[saveDataNum].accessory[characterNum][i] = accessory[i];
		saveDataList[saveDataNum].setSkill[characterNum][i] = setSkill[i];
	}

	for (int i = 0; i < Define::PLAYER_SKILL_MAX; i++)
	{
		saveDataList[saveDataNum].skillLevel[characterNum][i] = skillLevel[i];
		saveDataList[saveDataNum].skillEXP[characterNum][i] = skillEXP[i];
	}
}

int CharacterStatus::GetATK()const
{
	int atk = ATK;
	for (int i = 0; i != ATKMagnification.size(); i++)
	{
		if (ATKMagnification[i] > 0.001)
		{
			atk *= ATKMagnification[i];
		}
	}
	if ((HP / (double)MAX_HP) <= 0.3)
	{
		for (auto n : accessory)
		{
			if (n != -1)
			{
				if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_UNDER_30_PERCENT]>0.001)
				{
					atk *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_UNDER_30_PERCENT];
				}
			}
		}
	}
	return atk;
}

int CharacterStatus::GetINT()const
{
	int _int = INT;
	for (int i = 0; i != ATKMagnification.size(); i++)
	{
		if (INTMagnification[i] > 0.001)
		{
			_int *= INTMagnification[i];
		}
	}
	if ((HP / (double)MAX_HP) <= 0.3)
	{
		for (auto n : accessory)
		{
			if (n != -1)
			{
				if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_UNDER_30_PERCENT]>0.001)
				{
					_int *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_UNDER_30_PERCENT];
				}
			}
		}
	}
	return _int;
}

int CharacterStatus::GetDEF()const
{
	int def = DEF;
	for (int i = 0; i != ATKMagnification.size(); i++)
	{
		if (DEFMagnification[i] > 0.001)
		{
			def *= DEFMagnification[i];
		}
	}
	return def;
}

int CharacterStatus::GetRES()const
{
	int res = RES;
	for (int i = 0; i != ATKMagnification.size(); i++)
	{
		if (RESMagnification[i] > 0.001)
		{
			res *= RESMagnification[i];
		}
	}
	return res;
}