#pragma once

#include"Define.h"
#include"PlayerData.h"

class EnemyStatus
{
private:
	static string nameList[Define::ENEMY_KIND_NUM];
	static int LvList[Define::ENEMY_KIND_NUM];
	static int MAX_HPList[Define::ENEMY_KIND_NUM];
	static int ATKList[Define::ENEMY_KIND_NUM];
	static int DEFList[Define::ENEMY_KIND_NUM];
	static int INTList[Define::ENEMY_KIND_NUM];
	static int RESList[Define::ENEMY_KIND_NUM];
	static double walkSpeedList[Define::ENEMY_KIND_NUM];
	static double dashSpeedList[Define::ENEMY_KIND_NUM];
	static int dropEXPList[Define::ENEMY_KIND_NUM];
	static int dropMoneyList[Define::ENEMY_KIND_NUM];
	static array<vector<int>, Define::ENEMY_KIND_NUM> dropItemList;
	static array<vector<int>, Define::ENEMY_KIND_NUM> dropItemPercentList;
	static bool canMoveList[Define::ENEMY_KIND_NUM];
	static int moveIntervalUnnoticeList[Define::ENEMY_KIND_NUM];
	static int noticeDistanceList[Define::ENEMY_KIND_NUM];
	static double moveSpeedUnnoticeList[Define::ENEMY_KIND_NUM];
	static double moveSpeedNoticeList[Define::ENEMY_KIND_NUM];
private:
	int enemyKind;
	string name;
	int Lv;
	int HP;
	int ATK;
	int DEF;
	int INT;
	int RES;
	double walkSpeed;
	double dashSpeed;
	int dropEXP;
	int dropMoney;
	vector<int> dropItem;
	vector<int> dropItemPercent;
	bool canMove;
	int moveIntervalUnnotice;
	int noticeDistance;
	double moveSpeedUnnotice;
	double moveSpeedNotice;
public:
	EnemyStatus(int enemyKind);
	~EnemyStatus();
	static void Load();
	int CauseByPlayer(PlayerData* playerData, int sourceID, int skillKind, bool preAttack, bool SPMAX);
	void Death() { HP = 0; }

	int GetEnemyKind()const { return enemyKind; }
	string GetName()const { return name; }
	int GetLv()const { return Lv; }
	int GetHP()const { return HP; }
	int GetATK()const { return ATK; }
	int GetDEF()const { return DEF; }
	int GetINT()const { return INT; }
	int GetRES()const { return RES; }
	double GetWalkSpeed()const { return walkSpeed; }
	double GetDashSpeed()const { return dashSpeed; }
	double GetHPRate()const { return (double)HP / MAX_HPList[enemyKind]; }
	int GetDropEXP()const { return dropEXP; }
	int GetDropMoney()const { return dropMoney; }
	bool GetCanMove()const { return canMove; }
	int GetMoveIntervalUnnotice()const { return moveIntervalUnnotice; }
	int GetNoticeDistance()const { return noticeDistance; }
	double GetMoveSpeedUnnotice()const { return moveSpeedUnnotice; }
	double GetMoveSpeedNotice()const { return moveSpeedNotice; }
	const vector<int>& GetDropItem()const { return dropItem; }
	const vector<int>& GetDropItemPercent()const { return dropItemPercent; }
};