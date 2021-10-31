#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE036 :public BattleEffect
{
	vector<Vector2<int>> hitPositionList;
	EnemyStatus enemyStatus;
public:
	BattleEffectE036(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE036();
	void Update()override;
	void Draw()override;
};