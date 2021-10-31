#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE112 :public BattleEffect
{
	vector<Vector2<int>> hitPositionList;
	BossStatus bossStatus;
	int value1, value2;
public:
	BattleEffectE112(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int value1, int value2);
	~BattleEffectE112();
	void Update()override;
	void Draw()override;
};