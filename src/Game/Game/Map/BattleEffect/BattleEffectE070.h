#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE070 :public BattleEffect
{
private:
	static const double speed;
	static const int existTime;
private:
	vector<Vector2<int>> hitPositionList;
	Vector2<double> velocity;
	EnemyStatus enemyStatus;
public:
	BattleEffectE070(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE070();
	void Update()override;
	void Draw()override;
};