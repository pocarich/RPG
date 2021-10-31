#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE058 :public BattleEffect
{
private:
	static const int popNextTime = 10;
	static const int effectMax = 3;
private:
	int count;
	vector<Vector2<int>> hitPositionList;
	EnemyStatus enemyStatus;
public:
	BattleEffectE058(EnemyStatus enemyStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,int count);
	~BattleEffectE058();
	void Update()override;
	void Draw()override;
};