#pragma once

#include"BattleEffect.h"

class BattleEffectP100 :public BattleEffect
{
	bool SPMAX;
public:
	BattleEffectP100(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, bool SPMAX);
	~BattleEffectP100();
	void Update()override;
	void Draw()override;
};