#pragma once

#include"Define.h"
#include"Class.h"
#include"BattleEffect.h"
#include"PlayerData.h"
#include"EnemyMap.h"
#include"PeopleMap.h"
#include"BattleEffectP000.h"
#include"SystemMessage.h"
#include"TextUI.h"
#include"BossStatus.h"

class PlayerMap
{
private:
	static GHandle graph[Define::CHARACTER_NUM][(int)Direction::SIZE * 3];
	static GHandle conditionErrorGraph[(int)ConditionError::SIZE];
private:
	int id;
	BattleEffectP000* guardEffect;
	SystemMessage* systemMessage;
	list<BattleEffectPtr>& battleEffectList;
	list<BossMapPtr>& bossMapList;
	list<ObjectMapPtr>& objectMapList;
	list<TextUIPtr>& textUIList;
	list<DropItemPtr>& dropItemList;
	PlayerData* playerData;
	list<EnemyMapPtr>& enemyMapList;
	list<PeopleMapPtr>& peopleMapList;
	Vector2<int> masuPosition;
	Vector2<double> position;
	Direction direction;
	MoveState moveState;
	int& mapNum;

	int dispConditionTimer;
	int dispConditionNum;

	Vector2<double> velocity;
	int moveTime;
	int moveEndTime;

	bool mapChangeFlag;
	int attackKind;

	Vector2<double>& camera;

	int peopleNum;
	int eventNum;
	int specialEventNum;

	int stiffTimer;
	int guardCounter;

	bool knockBackFlag;
	int knockBackTimer;
	bool deathFlag;
	Vector2<double> knockBackVelocity;
	Direction knockBackDirection;
private:
	void UpdateConditionError();
	void UpdateKnockBack();
	void Guard();
	void MapChangeEnter();
	void UpdateMove();
	void StartMove();
	void ChangeDirection();
	void Move();
	bool CanMoveToNextPosition(Vector2<int> nextPosition,Direction nextDirection);
	void Attack();
	void StartAttack();
	void HappenEvent();
	void TalkToPeople();
	void CheckEvent();
	void ThroughOnEvent();
	void ChangeCharacter();
	void UpdateStiffTimer();
	void PickDropItem();
	void CheckAchieve();
public:
	static void Load();
	PlayerMap(PlayerData* playerData, SystemMessage* systemMessage, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,Vector2<double>& camera,list<BattleEffectPtr>& battleEffectList, list<DropItemPtr>& dropItemList, list<TextUIPtr>& textUIList,int& mapNum, array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int loadDataNum);
	~PlayerMap();
	void Update();
	void CheckDeath();
	void Draw();
	void ResetMapChangeFlag() { mapChangeFlag = false; }
	void MapChange();
	void ResetEvent();
	void ResetSpecialEvent();
	void CauseByEnemy(EnemyStatus enemyStatus, Direction attackDirection, int souceID, int skillKind);
	void CauseByBoss(BossStatus bossStatus, Direction attackDirection, int souceID, int skillKind);
	void SetSpecialEventNum(int n) { specialEventNum = n; }
	void Save(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int saveDataNum);

	int GetID()const { return id; }
	Vector2<int> GetMasuPosition()const { return masuPosition; }
	Vector2<double> GetPosition()const { return position; }
	bool GetMapChangeFlag()const { return mapChangeFlag; }
	int GetPeopleNum()const { return peopleNum; }
	int GetEventNum()const { return eventNum; }
	int GetSpecialEventNum()const { return specialEventNum; }
	Direction GetDirection()const { return direction; }
	bool GetDeathFlag()const { return deathFlag; }
};