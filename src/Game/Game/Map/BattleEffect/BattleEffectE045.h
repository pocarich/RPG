#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE045 :public BattleEffect
{
private:
	static const int createNextEffectTime = 7;
	static const int effectMax = 9;
private:
	int count;
	EnemyStatus enemyStatus;
public:
	BattleEffectE045(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int count);
	~BattleEffectE045();
	void Update()override;
	void Draw()override;
};