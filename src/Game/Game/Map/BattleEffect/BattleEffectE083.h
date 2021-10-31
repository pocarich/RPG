#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE083 :public BattleEffect
{
	EnemyStatus enemyStatus;
public:
	BattleEffectE083(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE083();
	void Update()override;
	void Draw()override;
};