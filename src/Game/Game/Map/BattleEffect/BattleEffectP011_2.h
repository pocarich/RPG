#pragma once

#include"BattleEffect.h"

class BattleEffectP011_2 :public BattleEffect
{
	vector<Vector2<int>> hitPositionList;
	bool SPMAX;
public:
	BattleEffectP011_2(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX);
	~BattleEffectP011_2();
	void Update()override;
	void Draw()override;
};