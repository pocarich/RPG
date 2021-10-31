#pragma once

#include"BattleEffect.h"

class BattleEffectP101 :public BattleEffect
{
private:
	static const double speed;
	static const int existTime;
private:
	Direction direction;
	Vector2<double> velocity;
	bool SPMAX;
public:
	BattleEffectP101(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, bool SPMAX);
	~BattleEffectP101();
	void Update()override;
	void Draw()override;
};