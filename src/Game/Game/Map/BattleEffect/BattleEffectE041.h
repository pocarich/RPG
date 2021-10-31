#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE041 :public BattleEffect
{
	EnemyStatus enemyStatus;
public:
	BattleEffectE041(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE041();
	void Update()override;
	void Draw()override;
};