#pragma once

#include"Define.h"
#include"Class.h"
#include"BossStatus.h"
#include"PlayerData.h"
#include"TextUI.h"


class PlayerMap;

class BossMap
{
protected:
	static GHandle graph[Define::BOSS_KIND_NUM];
protected:
	enum struct StartMoveKind
	{
		RAMDOM,
		CLOSE,
		ALIGNMENT,
		AWAY
	};
protected:
	int id;
	int kind;
	PlayerData* playerData;
	PlayerMap* playerMap;
	list<TextUIPtr>& textUIList;
	list<BattleEffectPtr>& battleEffectList;
	list<EnemyMapPtr>& enemyMapList;
	list<ObjectMapPtr>& objectMapList;
	list<PeopleMapPtr>& peopleMapList;
	list<BossMapPtr>& bossMapList;
	list<DropItemPtr>& dropItemList;
	BossStatus* bossStatus;
	vector<Vector2<int>> masuPosition;
	Vector2<double> position;
	Direction direction;
	MoveState moveState;
	int& mapNum;

	Vector2<double> velocity;
	int moveTime;
	int moveEndTime;

	Vector2<double>& camera;
	bool deathFlag;

	bool damagedFlag;
	int damagedTimer;

	bool knockBackFlag;
	int knockBackTimer;
	Vector2<double> knockBackVelocity;
	Direction knockBackDirection;

	int moveIntervalTimer;

	int stiffTimer;
	int stiffTime;
	int delay;
	double speed;

	int state;
	int state1;
	int preAttackKind;
	int moveCounter;
	int werpCounter;
	int tempAttackKind;

	vector<Vector2<int>> attackPointList;

	int attackKind;
	int attackTimer;
	Direction attackDirection;
	int standFlag;
	int specialEventNum;
	int setStiffTime;
	int setAttackTime;
protected:
	virtual void UpdateNotice() = 0;
	void UpdateMoveIntervalTimer();
	void StartMove(double _speed, StartMoveKind startMoveKind);
	bool StartMove(double _speed, Direction direction);
	void UpdateDamagedTimer();
	void UpdateKnockBack();
	void Move();
	void UpdateStiffTimer();
	bool CanMoveToNextPosition(Vector2<int> next,Direction nextDirection);
	void UpdateAttackTimer();
public:
	BossMap(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int id, int kind,Vector2<int> masuPosition, Vector2<double>& camera,int& mapNum,int standFlag,int specialEventNum);
	virtual ~BossMap();
	static void Load();
	virtual void Update();
	virtual void Draw();
	void DrawHP();
	void DrawAttackPoint();
	void Death();
	void CauseByPlayer(int sourceID, int skillKind, bool SPMAX);
	bool GetDeathFlag()const { return deathFlag; }
	const vector<Vector2<int>>& GetMasuPosition()const { return masuPosition; }
	Vector2<double> GetPosition()const { return position; }
	int GetID()const { return id; }
	const BossStatus* GetBossStatus()const { return bossStatus; }
	int GetSpecialEventNum()const { return specialEventNum; }
};