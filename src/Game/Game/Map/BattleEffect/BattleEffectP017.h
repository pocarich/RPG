#pragma once

#include"BattleEffect.h"

class BattleEffectP017 :public BattleEffect
{
private:
	static const int existTime = 300;
	static const int hitInterval = 20;
	bool SPMAX;
public:
	BattleEffectP017(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, bool SPMAX);
	~BattleEffectP017();
	void Update()override;
	void Draw()override;
};