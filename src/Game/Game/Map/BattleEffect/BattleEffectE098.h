#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE098 :public BattleEffect
{
private:
	static const int interval = 20;
private:
	vector<Vector2<int>> hitPositionList;
	BossStatus bossStatus;
public:
	BattleEffectE098(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE098();
	void Update()override;
	void Draw()override;
};