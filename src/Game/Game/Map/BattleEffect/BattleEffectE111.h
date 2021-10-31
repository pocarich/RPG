#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE111 :public BattleEffect
{
private:
	static const int interval = 15;
private:
	array<vector<Vector2<int>>, 3> hitPositionList;
	BossStatus bossStatus;
public:
	BattleEffectE111(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE111();
	void Update()override;
	void Draw()override;
};