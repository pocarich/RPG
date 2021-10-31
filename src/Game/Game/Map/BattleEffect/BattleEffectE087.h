#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE087 :public BattleEffect
{
private:
	static const double speed;
	static const int existTime;
	static const int hitInterval;
private:
	Direction direction;
	Vector2<double> velocity;
	BossStatus bossStatus;
public:
	BattleEffectE087(BossStatus bossStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE087();
	void Update()override;
	void Draw()override;
};