#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE126 :public BattleEffect
{
private:
	static const double speed;
	static const int existTime;
	static const int hitInterval;
private:
	vector<Vector2<int>> hitPositionList;
	Direction direction;
	Vector2<double> velocity;
	BossStatus bossStatus;
	int subMoveCounter;
	int subState;
	int subLevel;
public:
	BattleEffectE126(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE126();
	void Update()override;
	void Draw()override;
};