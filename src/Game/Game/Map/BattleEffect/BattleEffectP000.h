#pragma once

#include"BattleEffect.h"

class BattleEffectP000 :public BattleEffect
{
	Vector2<double>& playerPosition;
public:
	BattleEffectP000(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, Vector2<double>& playerPosition);
	~BattleEffectP000();
	void Update()override;
	void Draw()override;
};