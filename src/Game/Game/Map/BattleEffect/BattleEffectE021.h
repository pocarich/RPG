#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE021 :public BattleEffect
{
private:
	static const int createNextEffectTime = 7;
	static const int effectMax = 6;
private:
	int count;
	EnemyStatus enemyStatus;
public:
	BattleEffectE021(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,int count);
	~BattleEffectE021();
	void Update()override;
	void Draw()override;
};