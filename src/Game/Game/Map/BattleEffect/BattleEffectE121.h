#pragma once

#include"BattleEffect.h"
#include"BossStatus.h"

class BattleEffectE121 :public BattleEffect
{
private:
	static const double speed;
	static const int existTime;
private:
	vector<Vector2<int>> hitPositionList;
	Vector2<double> velocity;
	BossStatus bossStatus;
	int changeDirectionCounter;
public:
	BattleEffectE121(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum);
	~BattleEffectE121();
	void Update()override;
	void Draw()override;
};