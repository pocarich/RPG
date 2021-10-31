#include"../header/BattleEffectE095.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE095::BattleEffectE095(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, bool seedFlag, int counter) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus), seedFlag(seedFlag),counter(counter)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectE095::~BattleEffectE095()
{

}

void BattleEffectE095::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			playerMap->CauseByBoss(bossStatus, direction, sourceID, 95);
		}
	}
	if (effectTimer == interval&&seedFlag && (counter + 1) != maxCounter)
	{
		bool hitFlag = false;
		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
		if (abs(diff.x) <= abs(diff.y))
		{
			if (diff.y > 0)
			{
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					Vector2<int> next = masuPosition + Vector2<int>(i, j) + Vector2<int>(0, 1);
					Vector2<double> tempPos = Vector2<double>(next.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, next.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
					if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
					{
						hitFlag = true;
					}
				}
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					Vector2<int> next = masuPosition + Vector2<int>(i, j) + Vector2<int>(0, 1);
					battleEffectList.push_back(make_shared<BattleEffectE095>(bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, next, direction, camera, mapNum, i == 0 && j == 0, hitFlag ? (maxCounter - 1) : (counter + 1)));
				}
			}
			else
			{
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					Vector2<int> next = masuPosition + Vector2<int>(i, j) + Vector2<int>(0, -1);
					Vector2<double> tempPos = Vector2<double>(next.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, next.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
					if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
					{
						hitFlag = true;
					}
				}
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					Vector2<int> next = masuPosition + Vector2<int>(i, j) + Vector2<int>(0, -1);
					battleEffectList.push_back(make_shared<BattleEffectE095>(bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, next, direction, camera, mapNum, i == 0 && j == 0, hitFlag ? (maxCounter - 1) : (counter + 1)));
				}
			}
		}
		else
		{
			if (diff.x > 0)
			{
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					Vector2<int> next = masuPosition + Vector2<int>(i, j) + Vector2<int>(1, 0);
					Vector2<double> tempPos = Vector2<double>(next.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, next.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
					if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
					{
						hitFlag = true;
					}
				}
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					Vector2<int> next = masuPosition + Vector2<int>(i, j) + Vector2<int>(1, 0);
					battleEffectList.push_back(make_shared<BattleEffectE095>(bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, next, direction, camera, mapNum, i == 0 && j == 0, hitFlag ? (maxCounter - 1) : (counter + 1)));
				}
			}
			else
			{
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					Vector2<int> next = masuPosition + Vector2<int>(i, j) + Vector2<int>(-1, 0);
					Vector2<double> tempPos = Vector2<double>(next.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, next.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
					if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
					{
						hitFlag = true;
					}
				}
				for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
				{
					Vector2<int> next = masuPosition + Vector2<int>(i, j) + Vector2<int>(-1, 0);
					battleEffectList.push_back(make_shared<BattleEffectE095>(bossStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, next, direction, camera, mapNum, i == 0 && j == 0, hitFlag ? (maxCounter - 1) : (counter + 1)));
				}
			}
		}

	}
	if (effectTimer == 24)
	{
		disappearFlag = true;
	}
}

void BattleEffectE095::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[22][(effectTimer / 3) % 8], TRUE);
}