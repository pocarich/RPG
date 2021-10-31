#pragma once

#include"BattleEffect.h"

class BattleEffectP016 :public BattleEffect
{
private:
	static const int createNextEffectTime = 6;
	static const int effectMax = 15;
private:
	int count;
	bool SPMAX;
public:
	BattleEffectP016(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int count, bool SPMAX);
	~BattleEffectP016();
	void Update()override;
	void Draw()override;
};