#pragma once

#include"BattleEffect.h"

class BattleEffectP006 :public BattleEffect
{
private:
	static const int offset;
private:
	vector<Vector2<int>> hitPositionList;
	bool SPMAX;
public:
	BattleEffectP006(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX);
	~BattleEffectP006();
	void Update()override;
	void Draw()override;
};