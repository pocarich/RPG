#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE123 :public BattleEffect
{
	vector<Vector2<int>> hitPositionList;
	BossStatus bossStatus;
public:
	BattleEffectE123(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE123();
	void Update()override;
	void Draw()override;
};