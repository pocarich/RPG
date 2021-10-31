#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE095 :public BattleEffect
{
private:
	static const int maxCounter = 10;
	static const int interval = 10;
private:
	BossStatus bossStatus;
	bool seedFlag;
	int counter;
public:
	BattleEffectE095(BossStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, bool seedFlag, int counter);
	~BattleEffectE095();
	void Update()override;
	void Draw()override;
};