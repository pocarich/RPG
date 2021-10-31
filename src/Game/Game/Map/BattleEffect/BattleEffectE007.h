#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE007 :public BattleEffect
{
	EnemyStatus enemyStatus;
public:
	BattleEffectE007(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE007();
	void Update()override;
	void Draw()override;
};