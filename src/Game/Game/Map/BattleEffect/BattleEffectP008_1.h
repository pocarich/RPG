#pragma once

#include"BattleEffect.h"

class BattleEffectP008_1 :public BattleEffect
{
private:
	static const double speed;
	static const int existTime;
	bool SPMAX;
private:
	Vector2<double> velocity;
public:
	BattleEffectP008_1(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX);
	~BattleEffectP008_1();
	void Update()override;
	void Draw()override;
};