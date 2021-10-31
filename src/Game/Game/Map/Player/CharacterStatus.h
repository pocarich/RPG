#pragma once

#include"Define.h"
#include"BossStatus.h"
#include"SaveData.h"

class EnemyStatus;

class CharacterStatus
{
private:
	static const int autoHeelInterval = 6;
public:
	static string nameList[Define::CHARACTER_NUM];
	static int defaultLv[Define::CHARACTER_NUM];
	static int BaseHP[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
	static int BaseSP[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
	static int BaseATK[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
	static int BaseDEF[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
	static int BaseINT[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
	static int BaseRES[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
	static int NeedEXP[Define::CHARACTER_NUM][Define::MAX_LEVEL+1];
	static array<array<vector<int>, Define::MAX_LEVEL + 1>, Define::CHARACTER_NUM> LearnSkill;
	static array<vector<int>,Define::CHARACTER_NUM> CanEquipWeapon;
	static array<vector<int>, Define::CHARACTER_NUM> CanEquipHead;
	static array<vector<int>, Define::CHARACTER_NUM> CanEquipChest;
	static array<vector<int>, Define::CHARACTER_NUM> CanEquipAccessory;
	static int defaultSetSkill[Define::CHARACTER_NUM][3];
private:
	int characterNum;
	string name;
	int Lv;
	int HP;
	int MAX_HP;
	int SP;
	int MAX_SP;
	int ATK;
	int DEF;
	int INT;
	int RES;
	int EXP;
	array<double,2> ATKMagnification;
	array<double, 2> DEFMagnification;
	array<double, 2> INTMagnification;
	array<double, 2> RESMagnification;
	int reduceSPUse;
	int reduceStiff;
	int reduceStiffTimer;
	int reduceSPUseTimer;
	array<int,2> ATKMagnificationTimer;
	array<int, 2> DEFMagnificationTimer;
	array<int, 2> INTMagnificationTimer;
	array<int, 2> RESMagnificationTimer;
	double normalMagnification;
	double skillMagnification;
	int autoHeelHPAmount;
	int autoHeelSPAmount;
	int autoHeelTimer;
	vector<int> learnSkillList;
	int weapon;
	int head;
	int chest;
	array<int,3> accessory;
	array<int,3> setSkill;
	array<int, Define::PLAYER_SKILL_MAX> skillLevel;
	array<int, Define::PLAYER_SKILL_MAX> skillEXP;
	array<bool, (int)ConditionError::SIZE> conditionError;
	array<int, (int)ConditionError::SIZE> conditionErrorTimer;
	vector<int> canEquipWeapon;
	vector<int> canEquipHead;
	vector<int> canEquipChest;
	vector<int> canEquipAccessory;
private:
	void UpdateStatus(bool LvUp);
	void UpdateMagnification();
	void UpdateAutoHeel();
public:
	CharacterStatus(int characterNum, array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int loadDataNum);
	~CharacterStatus();
	static void Load();
	void UpdateMap();
	void Hit(int value,int skillNum);
	void UpdateConditionError();
	void UpdateConditionErrorTimer();
	void AddEXP(int value);
	void Damage(int damage);
	void UseItem(int itemKind);
	void PaySP(int skillKind);
	void SetSkill(int i, int skillKind);
	void SetWeapon(int itemKind);
	void SetHead(int itemKind); 
	void SetChest(int itemKind); 
	void SetAccessory(int i, int itemKind);
	void RemoveWeapon();
	void RemoveHead();
	void RemoveChest();
	void RemoveAccessory(int num);
	void CauseSkill(int skillKind);
	void AddSkill();
	void UseINN();
	void AddSkillEXP(int skillKind);
	int CauseByEnemy(EnemyStatus enemyStatus, int sourceID, int skillKind,bool stiffFlag,bool guardFlag,int guardCounter);
	int CauseByBoss(BossStatus bossStatus, int sourceID, int skillKind,bool stiffFlag,bool guardFlag,int guardCounter);
	void Save(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList,int saveDataNum);

	string GetName()const { return name; }
	int GetHP()const { return HP; }
	int GetMAX_HP()const { return MAX_HP; }
	int GetSP()const { return SP; }
	int GetMAX_SP()const { return MAX_SP; }
	int GetATK()const;
	int GetDEF()const;
	int GetINT()const;
	int GetRES()const;
	int GetEXP()const { return EXP; }
	int GetLv()const { return Lv; }
	const vector<int>& GetLearnSkillList()const { return learnSkillList; }
	int GetWeapon()const { return weapon; }
	int GetHead()const { return head; }
	int GetChest()const { return chest; }
	const array<int, 3>& GetAccessory()const { return accessory; }
	const array<int, 3>& GetSetSkill()const { return setSkill; }
	const vector<int>& GetCanEquipWeapon()const { return canEquipWeapon; }
	const vector<int>& GetCanEquipHead()const { return canEquipHead; }
	const vector<int>& GetCanEquipChest()const { return canEquipChest; }
	const vector<int>& GetCanEquipAccessory()const { return canEquipAccessory; }
	const array<int, Define::PLAYER_SKILL_MAX>& GetSkillLevel()const { return skillLevel; }
	const array<int, Define::PLAYER_SKILL_MAX>& GetSkillEXP()const { return skillEXP; }
	const array<bool, (int)ConditionError::SIZE>& GetConditionError()const { return conditionError; }
	const array<int, (int)ConditionError::SIZE>& GetConditionErrorTimer()const { return conditionErrorTimer; }
	double GetNormalMagnification()const { return normalMagnification; }
	double GetSkillMagnification()const { return skillMagnification; }
	int GetReduceStiff()const { return reduceStiff; }
	int GetReduceSPUse()const { return reduceSPUse; }
	int GetCharacterNum()const { return characterNum; }
};