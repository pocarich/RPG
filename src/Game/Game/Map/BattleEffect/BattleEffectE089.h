#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE089 :public BattleEffect
{
	vector<Vector2<int>> hitPositionList;
	BossStatus bossStatus;
public:
	BattleEffectE089(BossStatus bossStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE089();
	void Update()override;
	void Draw()override;
};