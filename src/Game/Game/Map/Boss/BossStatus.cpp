#include"../header/BossStatus.h"
#include"../header/Function.h"
#include"../header/CharacterSkillInfoList.h"
#include"../header/PlayerData.h"
#include"../header/ItemInfoList.h"

string BossStatus::nameList[Define::BOSS_KIND_NUM];
int BossStatus::LvList[Define::BOSS_KIND_NUM];
int BossStatus::MAX_HPList[Define::BOSS_KIND_NUM];
int BossStatus::ATKList[Define::BOSS_KIND_NUM];
int BossStatus::DEFList[Define::BOSS_KIND_NUM];
int BossStatus::INTList[Define::BOSS_KIND_NUM];
int BossStatus::RESList[Define::BOSS_KIND_NUM];
int BossStatus::dropEXPList[Define::BOSS_KIND_NUM];
int BossStatus::dropMoneyList[Define::BOSS_KIND_NUM];
array<vector<int>, Define::BOSS_KIND_NUM> BossStatus::dropItemList;

BossStatus::BossStatus(int enemyKind) :enemyKind(enemyKind)
{
	name = nameList[enemyKind];
	Lv = LvList[enemyKind];
	HP = MAX_HPList[enemyKind];
	ATK = ATKList[enemyKind];
	DEF = DEFList[enemyKind];
	INT = INTList[enemyKind];
	RES = RESList[enemyKind];
	dropEXP = dropEXPList[enemyKind];
	dropMoney = dropMoneyList[enemyKind];
	dropItem = dropItemList[enemyKind];
}

BossStatus::~BossStatus()
{

}

void BossStatus::Load()
{
	ifstream ifs;

	ifs.open("data/csv/enemy/BossStatus.csv");

	assert(!ifs.fail() && "BossStatus::Load()");

	string readString;

	for (int i = 0; i < Define::BOSS_KIND_NUM; i++)
	{
		getline(ifs, readString);
		auto element = Function::split(readString, ',');
		assert(element.size() == 10 && "BossStatus::Load() サイズが不正です。");

		for (int k = 0; k != element.size(); k++)
		{
			int num;
			stringstream ss;
			ss << element[k];
			switch (k)
			{
			case 0:
				ss >> nameList[i];
				break;
			case 1:
				ss >> LvList[i];
				break;
			case 2:
				ss >> MAX_HPList[i];
				break;
			case 3:
				ss >> ATKList[i];
				break;
			case 4:
				ss >> DEFList[i];
				break;
			case 5:
				ss >> INTList[i];
				break;
			case 6:
				ss >> RESList[i];
				break;
			case 7:
				ss >> dropEXPList[i];
				break;
			case 8:
				ss >> dropMoneyList[i];
				break;
			case 9:
			{
				auto element2 = Function::split(ss.str(), '|');
				for (int j = 0; j != element2.size(); j++)
				{
					if (element2[j] == "#")
					{
						break;
					}
					int num;
					stringstream ss2;
					ss2 << element2[j];
					ss2 >> num;
					dropItemList[i].push_back(num);
				}
			}
			break;
			}
		}
	}

	ifs.close();
}

int BossStatus::CauseByPlayer(PlayerData* playerData, int sourceID, int skillKind,bool preAttack,bool SPMAX)
{
	int value = 0;
	switch (skillKind)
	{
	case 100:
		value = max(1, (playerData->GetCharacterStatusList()[sourceID]->GetATK()*playerData->GetCharacterStatusList()[sourceID]->GetNormalMagnification()*(1 + (playerData->GetCharacterStatusList()[sourceID]->GetLv() - 1)*0.04) - DEF));
		if (preAttack)
		{
			double damagePercent = 1.0;
			for (auto n : playerData->GetCharacterStatusList()[sourceID]->GetAccessory())
			{
				if (n != -1)
				{
					if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_TO_PREACTION_PERCENT] > 0.001)
					{
						damagePercent *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_TO_PREACTION_PERCENT];
					}
				}
			}
			value *= damagePercent;
			value = max(1, value);
		}
		if (SPMAX)
		{
			double damagePercent = 1.0;
			for (auto n : playerData->GetCharacterStatusList()[sourceID]->GetAccessory())
			{
				if (n != -1)
				{
					if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT] > 0.001)
					{
						damagePercent *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT];
					}
				}
			}
			value *= damagePercent;
			value = max(1, value);
		}
		value = value - value*0.1 + value*0.2*((GetRand(10000) % 100) / 100.0);
		HP -= value;
		break;
	case 101:
		value = max(1, (playerData->GetCharacterStatusList()[sourceID]->GetINT()*playerData->GetCharacterStatusList()[sourceID]->GetNormalMagnification()*(1 + (playerData->GetCharacterStatusList()[sourceID]->GetLv() - 1)*0.04) - RES));
		value *= 0.7;
		if (preAttack)
		{
			double damagePercent = 1.0;
			for (auto n : playerData->GetCharacterStatusList()[sourceID]->GetAccessory())
			{
				if (n != -1)
				{
					if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_TO_PREACTION_PERCENT] > 0.001)
					{
						damagePercent *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_TO_PREACTION_PERCENT];
					}
				}
			}
			value *= damagePercent;
			value = max(1, value);
		}
		if (SPMAX)
		{
			double damagePercent = 1.0;
			for (auto n : playerData->GetCharacterStatusList()[sourceID]->GetAccessory())
			{
				if (n != -1)
				{
					if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT] > 0.001)
					{
						damagePercent *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT];
					}
				}
			}
			value *= damagePercent;
			value = max(1, value);
		}
		value = value - value*0.1 + value*0.2*((GetRand(10000) % 100) / 100.0);
		HP -= value;
		break;
	default:
		if (CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].attribute[(int)PlayerSkillAttribute::TYPE] == 0)
		{
			value += (playerData->GetCharacterStatusList()[sourceID]->GetATK()*playerData->GetCharacterStatusList()[sourceID]->GetSkillMagnification()*(1 + (playerData->GetCharacterStatusList()[sourceID]->GetLv() - 1)*0.04) - DEF);
		}
		else
		{
			value += (playerData->GetCharacterStatusList()[sourceID]->GetINT()*playerData->GetCharacterStatusList()[sourceID]->GetSkillMagnification()*(1 + (playerData->GetCharacterStatusList()[sourceID]->GetLv() - 1)*0.04) - RES);
		}
		value *= CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].value[playerData->GetCharacterStatusList()[sourceID]->GetSkillLevel()[skillKind] - 1];
		
		if (preAttack)
		{
			double damagePercent = 1.0;
			for (auto n : playerData->GetCharacterStatusList()[sourceID]->GetAccessory())
			{
				if (n != -1)
				{
					if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_TO_PREACTION_PERCENT] > 0.001)
					{
						damagePercent *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_TO_PREACTION_PERCENT];
					}
				}
			}
			value *= damagePercent;
			value = max(1, value);
		}
		if (SPMAX)
		{
			double damagePercent = 1.0;
			for (auto n : playerData->GetCharacterStatusList()[sourceID]->GetAccessory())
			{
				if (n != -1)
				{
					if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT] > 0.001)
					{
						damagePercent *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT];
					}
				}
			}
			value *= damagePercent;
			value = max(1, value);
		}
		value = value - value*0.1 + value*0.2*((GetRand(10000) % 100) / 100.0);
		value = max(1, value);
		HP -= value;
		break;
	}

	HP = max(min(HP, MAX_HPList[enemyKind]), 0);

	playerData->GetCharacterStatusList()[sourceID]->Hit(value, skillKind);

	return value;
}
