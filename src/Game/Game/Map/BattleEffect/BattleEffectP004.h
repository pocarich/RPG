#pragma once

#include"BattleEffect.h"

class BattleEffectP004 :public BattleEffect
{
	bool SPMAX;
public:
	BattleEffectP004(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX);
	~BattleEffectP004();
	void Update()override;
	void Draw()override;
};