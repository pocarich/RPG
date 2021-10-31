#pragma once

#include"BattleEffect.h"

class BattleEffectP024 :public BattleEffect
{
	vector<Vector2<int>> hitPositionList;
	int alpha;
	bool SPMAX;
public:
	BattleEffectP024(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, bool SPMAX);
	~BattleEffectP024();
	void Update()override;
	void Draw()override;
};