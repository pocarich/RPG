#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE085 :public BattleEffect
{
private:
	static const int nextPopTime = 5;
	static const int stateMax = 5;
private:
	int offset;
	int stateCount;
	BossStatus bossStatus;
public:
	BattleEffectE085(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int stateCount, int offset);
	~BattleEffectE085();
	void Update()override;
	void Draw()override;
};