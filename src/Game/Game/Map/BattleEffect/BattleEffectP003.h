#pragma once

#include"BattleEffect.h"

class BattleEffectP003 :public BattleEffect
{
private:
	static const double speed;
	static const int existTime;
	bool SPMAX;
private:
	Direction direction;
	Vector2<double> velocity;
public:
	BattleEffectP003(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX);
	~BattleEffectP003();
	void Update()override;
	void Draw()override;
};