#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE124_1 :public BattleEffect
{
	BossStatus bossStatus;
public:
	BattleEffectE124_1(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE124_1();
	void Update()override;
	void Draw()override;
};