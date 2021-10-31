#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE028_2 :public BattleEffect
{
	EnemyStatus enemyStatus;
public:
	BattleEffectE028_2(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE028_2();
	void Update()override;
	void Draw()override;
};