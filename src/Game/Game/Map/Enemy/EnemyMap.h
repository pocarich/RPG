#pragma once

#include"Define.h"
#include"Class.h"
#include"EnemyStatus.h"
#include"PlayerData.h"
#include"TextUI.h"


class PlayerMap;

class EnemyMap
{
protected:
	static GHandle graph[Define::ENEMY_KIND_NUM];
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
	list<BossMapPtr>& bossMapList;
	list<ObjectMapPtr>& objectMapList;
	list<PeopleMapPtr>& peopleMapList;
	list<EnemyMapPtr>& enemyMapList;
	list<DropItemPtr>& dropItemList;
	EnemyStatus* enemyStatus;
	Vector2<int> masuPosition;
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

	bool noticeFlag;
	int moveIntervalTimer;

	int stiffTimer;
	int setAttackTime;
	int setStiffTime;
	int subState;
	int moveCounter;

	vector<Vector2<int>> attackPointList;

	int attackKind;
	int attackTimer;
	Direction attackDirection;
protected:
	virtual void UpdateNotice() = 0;
	virtual void UpdateMoveUnnotice();
	void UpdateMoveIntervalTimer();
	void StartMove(double _speed, StartMoveKind startMoveKind);
	void Notice();
	void UpdateDamagedTimer();
	void UpdateKnockBack();
	void Move();
	void UpdateStiffTimer();
	bool CanMoveToNextPosition(Vector2<int> next,Direction nextDirection);
	void UpdateAttackTimer();
public:
	EnemyMap(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,int id,Vector2<int> masuPosition, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum);
	virtual ~EnemyMap();
	static void Load();
	virtual void Update();
	virtual void Draw();
	void DrawHP();
	void DrawAttackPoint();
	void Death();
	void CauseByPlayer(int sourceID, int skillKind, bool SPMAX);
	bool GetDeathFlag()const { return deathFlag; }
	Vector2<int> GetMasuPosition()const { return masuPosition; }
	Vector2<double> GetPosition()const { return position; }
	int GetID()const { return id; }
	const EnemyStatus* GetEnemyStatus()const { return enemyStatus; }
};