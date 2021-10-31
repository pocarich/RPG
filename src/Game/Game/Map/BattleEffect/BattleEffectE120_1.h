#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE120_1 :public BattleEffect
{
private:
	static const double speed;
	static const int existTime;
private:
	Direction direction;
	Vector2<double> velocity;
	BossStatus bossStatus;
public:
	BattleEffectE120_1(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE120_1();
	void Update()override;
	void Draw()override;
};