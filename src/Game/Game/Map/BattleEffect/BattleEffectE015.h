#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE015 :public BattleEffect
{
	EnemyStatus enemyStatus;
public:
	BattleEffectE015(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE015();
	void Update()override;
	void Draw()override;
};