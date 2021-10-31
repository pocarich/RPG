#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE129 :public BattleEffect
{
	BossStatus bossStatus;
	int alpha;
public:
	BattleEffectE129(BossStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE129();
	void Update()override;
	void Draw()override;
};