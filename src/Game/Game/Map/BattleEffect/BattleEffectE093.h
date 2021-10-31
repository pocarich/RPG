#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE093 :public BattleEffect
{
	BossStatus bossStatus;
public:
	BattleEffectE093(BossStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE093();
	void Update()override;
	void Draw()override;
};