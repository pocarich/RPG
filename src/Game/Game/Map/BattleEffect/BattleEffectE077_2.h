#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE077_2 :public BattleEffect
{
	vector<Vector2<int>> attackPositionList;
	EnemyStatus enemyStatus;
public:
	BattleEffectE077_2(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE077_2();
	void Update()override;
	void Draw()override;
};