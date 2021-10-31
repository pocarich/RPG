#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE109 :public BattleEffect
{
private:
	static const int nextPopTime = 5;
	static const int stateMax = 10;
private:
	int offset;
	int stateCount;
	EnemyStatus enemyStatus;
public:
	BattleEffectE109(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int stateCount, int offset);
	~BattleEffectE109();
	void Update()override;
	void Draw()override;
};