#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE125 :public BattleEffect
{
private:
	static const int StartReadyTime = 10;
private:
	BossStatus bossStatus;
	bool happenNextFlag;
public:
	BattleEffectE125(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE125();
	void Update()override;
	void Draw()override;
};