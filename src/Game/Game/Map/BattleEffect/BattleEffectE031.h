#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE031 :public BattleEffect
{
	vector<Vector2<int>> hitPositionList;
	EnemyStatus enemyStatus;
public:
	BattleEffectE031(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE031();
	void Update()override;
	void Draw()override;
};