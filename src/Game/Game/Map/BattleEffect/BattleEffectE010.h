#pragma once

#include"BattleEffect.h"
#include"EnemyStatus.h"

class BattleEffectE010 :public BattleEffect
{
public:
	enum struct EightDirection
	{
		UP,
		UPRIGHT,
		RIGHT,
		DOWNRIGHT,
		DOWN,
		DOWNLEFT,
		LEFT,
		UPLEFT,
		SIZE
	};
private:
	static const double speed;
	static const int existTime;
private:
	Vector2<double> velocity;
	EnemyStatus enemyStatus;
	EightDirection eightDirection;
public:
	BattleEffectE010(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction,EightDirection eightDirection, Vector2<double>&camera, int& mapNum);
	~BattleEffectE010();
	void Update()override;
	void Draw()override;
};