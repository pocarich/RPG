#include"../header/BattleEffectE112.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE112::BattleEffectE112(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int value1, int value2) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus), value1(value1), value2(value2)
{
	static const Vector2<int> offset1[] = { Vector2<int>(2, 0), Vector2<int>(1, 1), Vector2<int>(0, 2), Vector2<int>(-1, 1) };
	static const Vector2<int> offset2[] = { Vector2<int>(-2, 0),Vector2<int>(-1, -1), Vector2<int>(0, -2), Vector2<int>(1, -1) };

	switch (value1)
	{
	case 0:
		for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
		{
			if (abs(i) + abs(j) <= 1)
			{
				hitPositionList.push_back(this->masuPosition + offset1[value2] + Vector2<int>(i, j));
			}
		}
		break;
	case 1:
		for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
		{
			if (abs(i) + abs(j) <= 1)
			{
				hitPositionList.push_back(this->masuPosition + offset2[value2] + Vector2<int>(i, j));
			}
		}
		break;
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE112::~BattleEffectE112()
{

}

void BattleEffectE112::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByBoss(bossStatus, direction, sourceID, 112);
			}
		}
	}
	if (effectTimer == 15)
	{
		if (value2 < 3)
		{
			battleEffectList.push_back(make_shared<BattleEffectE112>(bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, masuPosition, direction, camera, mapNum, value1, value2 + 1));
		}
	}
	if (effectTimer == 30)
	{
		disappearFlag = true;
	}
}

void BattleEffectE112::Draw()
{
	if (effectTimer < 30)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			DrawRotaGraphF((float)tempPos.x - camera.x, (float)tempPos.y - camera.y, 1.0, 0.0, graph[73][(effectTimer / 3) % 10], TRUE);
		}
	}

}