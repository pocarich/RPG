#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE116 :public BattleEffect
{
private:
	static const int nextPopTime = 5;
	static const int stateMax = 9;
private:
	int offset;
	int stateCount;
	BossStatus bossStatus;
public:
	BattleEffectE116(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int stateCount, int offset);
	~BattleEffectE116();
	void Update()override;
	void Draw()override;
};