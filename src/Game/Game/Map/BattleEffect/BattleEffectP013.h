#pragma once

#include"BattleEffect.h"

class BattleEffectP013 :public BattleEffect
{
	vector<Vector2<int>> hitPositionList;
	vector<Vector2<double>> drawPositionList;
	bool SPMAX;
public:
	BattleEffectP013(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX);
	~BattleEffectP013();
	void Update()override;
	void Draw()override;
};