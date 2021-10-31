#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE104 :public BattleEffect
{
	BossStatus bossStatus;
public:
	BattleEffectE104(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE104();
	void Update()override;
	void Draw()override;
};