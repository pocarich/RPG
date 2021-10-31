#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE086 :public BattleEffect
{
private:
	static const int popNextTime = 10;
	static const int effectMax = 4;
private:
	int count;
	vector<Vector2<int>> hitPositionList;
	BossStatus bossStatus;
public:
	BattleEffectE086(BossStatus bossStatus,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int count);
	~BattleEffectE086();
	void Update()override;
	void Draw()override;
};