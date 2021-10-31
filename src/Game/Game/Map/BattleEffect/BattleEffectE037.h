#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE037 :public BattleEffect
{
private:
	static const int interval = 20;
private:
	vector<Vector2<int>> hitPositionList;
	EnemyStatus enemyStatus;
public:
	BattleEffectE037(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE037();
	void Update()override;
	void Draw()override;
};