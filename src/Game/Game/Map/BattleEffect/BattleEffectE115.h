#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE115 :public BattleEffect
{
private:
	static const int nextPopTime = 5;
	static const int stateMax = 8;
private:
	int offset;
	int stateCount;
	BossStatus bossStatus;
public:
	BattleEffectE115(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int stateCount, int offset);
	~BattleEffectE115();
	void Update()override;
	void Draw()override;
};