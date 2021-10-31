#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE076 :public BattleEffect
{
	vector<Vector2<int>> attackPositionList;
	EnemyStatus enemyStatus;
public:
	BattleEffectE076(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE076();
	void Update()override;
	void Draw()override;
};