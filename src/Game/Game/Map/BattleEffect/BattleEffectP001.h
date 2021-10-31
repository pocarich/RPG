#pragma once

#include"BattleEffect.h"

class BattleEffectP001 :public BattleEffect
{
	vector<Vector2<int>> hitPositionList;
	bool SPMAX;
public:
	BattleEffectP001(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, bool SPMAX);
	~BattleEffectP001();
	void Update()override;
	void Draw()override;
};