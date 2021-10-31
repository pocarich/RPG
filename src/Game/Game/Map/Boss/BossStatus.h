#pragma once

#include"Define.h"

class PlayerData;

class BossStatus
{
public:
	static string nameList[Define::BOSS_KIND_NUM];
	static int LvList[Define::BOSS_KIND_NUM];
	static int MAX_HPList[Define::BOSS_KIND_NUM];
	static int ATKList[Define::BOSS_KIND_NUM];
	static int DEFList[Define::BOSS_KIND_NUM];
	static int INTList[Define::BOSS_KIND_NUM];
	static int RESList[Define::BOSS_KIND_NUM];
	static int dropEXPList[Define::BOSS_KIND_NUM];
	static int dropMoneyList[Define::BOSS_KIND_NUM];
	static array<vector<int>, Define::BOSS_KIND_NUM> dropItemList;
private:
	int enemyKind;
	int Lv;
	string name;
	int HP;
	int ATK;
	int DEF;
	int INT;
	int RES;
	int dropEXP;
	int dropMoney;
	vector<int> dropItem;
public:
	BossStatus(int enemyKind);
	~BossStatus();
	static void Load();
	int CauseByPlayer(PlayerData* playerData, int sourceID, int skillKind, bool preAttack, bool SPMAX);
	int GetEnemyKind()const { return enemyKind; }
	string GetName()const { return name; }
	int GetLv()const { return Lv; }
	int GetHP()const { return HP; }
	int GetATK()const { return ATK; }
	int GetDEF()const { return DEF; }
	int GetINT()const { return INT; }
	int GetRES()const { return RES; }
	double GetHPRate()const { return (double)HP / MAX_HPList[enemyKind]; }
	int GetDropEXP()const { return dropEXP; }
	int GetDropMoney()const { return dropMoney; }
	const vector<int>& GetDropItem()const { return dropItem; }
};