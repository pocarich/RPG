#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE128 :public BattleEffect
{
	BossStatus bossStatus;
public:
	BattleEffectE128(BossStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE128();
	void Update()override;
	void Draw()override;
};