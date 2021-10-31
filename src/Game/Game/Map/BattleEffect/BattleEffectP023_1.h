#pragma once

#include"BattleEffect.h"

class BattleEffectP023_1 :public BattleEffect
{
private:
	static const double speed;
	static const int existTime;
private:
	Direction direction;
	Vector2<double> velocity;
	bool SPMAX;
public:
	BattleEffectP023_1(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX);
	~BattleEffectP023_1();
	void Update()override;
	void Draw()override;
};