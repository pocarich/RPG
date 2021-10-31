#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE118 :public BattleEffect
{
	BossStatus bossStatus;
public:
	BattleEffectE118(BossStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE118();
	void Update()override;
	void Draw()override;
};