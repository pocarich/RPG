#pragma once

#include"BattleEffect.h"

class BattleEffectP023_2 :public BattleEffect
{
private:
	static const int hitInterval = 10;
	static const int existTime = 120;
private:
	vector<Vector2<int>> hitPositionList;
	bool SPMAX;
public:
	BattleEffectP023_2(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, bool SPMAX);
	~BattleEffectP023_2();
	void Update()override;
	void Draw()override;
};