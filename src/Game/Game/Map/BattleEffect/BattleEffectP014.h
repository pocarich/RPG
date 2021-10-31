#pragma once

#include"BattleEffect.h"

class BattleEffectP014 :public BattleEffect
{
private:
	static const double speed;
	static const int hitInterval;
	static const int existTime;
private:
	Vector2<double>& playerPosition;
	Vector2<double> offset;
	bool SPMAX;
	int posNum;
public:
	BattleEffectP014(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, Vector2<double>& playerPosition, int posKind,bool SPMAX);
	~BattleEffectP014();
	void Update()override;
	void Draw()override;
};