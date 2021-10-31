#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE119 :public BattleEffect
{
private:
	static const int hitInterval = 10;
	static const int existTime = 600;
private:
	EnemyStatus enemyStatus;
public:
	BattleEffectE119(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE119();
	void Update()override;
	void Draw()override;
};