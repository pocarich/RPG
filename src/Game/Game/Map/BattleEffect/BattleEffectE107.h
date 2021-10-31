#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE107 :public BattleEffect
{
private:
	static const int interval = 20;
private:
	vector<Vector2<int>> hitPositionList;
	EnemyStatus enemyStatus; 
public:
	BattleEffectE107(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE107();
	void Update()override;
	void Draw()override;
};