#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE120_2 :public BattleEffect
{
private:
	static const int hitInterval = 10;
	static const int existTime = 180;
private:
	vector<Vector2<int>> attackPositionList;
	BossStatus bossStatus;
public:
	BattleEffectE120_2(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE120_2();
	void Update()override;
	void Draw()override;
};