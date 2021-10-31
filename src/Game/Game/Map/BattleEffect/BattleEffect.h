#pragma once

#include"Define.h"
#include"Class.h"

class PlayerMap;

class BattleEffect
{
protected:
	static GHandle graph[100][30];
protected:
	PlayerMap* playerMap;
	list<BattleEffectPtr>& battleEffectList;
	list<EnemyMapPtr>& enemyMapList;
	list<BossMapPtr>& bossMapList;
	list<ObjectMapPtr>& objectMapList;
	ObjectType sourceType;
	int sourceID;
	Vector2<int> masuPosition;
	Vector2<double> position;
	Direction direction;
	Vector2<double>& camera;
	int& mapNum;
	TargetType targetType;
	int effectTimer;
	bool disappearFlag;
protected:
	bool CanMoveToNextPosition(Vector2<int> next, Direction nextDirection);
public:
	BattleEffect(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, ObjectType sourceType, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, TargetType targetType);
	virtual ~BattleEffect();
	static void Load();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool GetDisappearFlag()const { return disappearFlag; }
	int GetEffectTimer()const { return effectTimer; }
	TargetType GetTargetType()const { return targetType; }
};