#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE059 :public BattleEffect
{
	vector<Vector2<int>> attackPositionList;
	EnemyStatus enemyStatus;
public:
	BattleEffectE059(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE059();
	void Update()override;
	void Draw()override;
};