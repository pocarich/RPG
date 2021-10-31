#include"../header/BattleEffectE103.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE103::BattleEffectE103(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	for (int i = -7; i < 8; i++)
	{
		if (i < 0)
		{
			hitPositionList.push_back(masuPosition + Vector2<int>(i, i));
			hitPositionList.push_back(masuPosition + Vector2<int>(i, i - 1));
			hitPositionList.push_back(masuPosition + Vector2<int>(i - 1, i));
		}
		else
		{
			hitPositionList.push_back(masuPosition + Vector2<int>(i, i));
			hitPositionList.push_back(masuPosition + Vector2<int>(i, i + 1));
			hitPositionList.push_back(masuPosition + Vector2<int>(i + 1, i));
		}
	}
	for (int i = -7; i < 8; i++)
	{
		if (i < 0)
		{
			hitPositionList.push_back(masuPosition + Vector2<int>(i, -i));
			hitPositionList.push_back(masuPosition + Vector2<int>(i, -i + 1));
			hitPositionList.push_back(masuPosition + Vector2<int>(i - 1, -i));
		}
		else
		{
			hitPositionList.push_back(masuPosition + Vector2<int>(i, -i));
			hitPositionList.push_back(masuPosition + Vector2<int>(i, -i - 1));
			hitPositionList.push_back(masuPosition + Vector2<int>(i + 1, -i));
		}
	}
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectE103::~BattleEffectE103()
{

}

void BattleEffectE103::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByBoss(bossStatus, direction, sourceID, 103);
			}
		}
	}
	if (effectTimer == 27)
	{
		disappearFlag = true;
	}
}

void BattleEffectE103::Draw()
{
	if (effectTimer < 27)
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[67][((effectTimer) / 3) % 9], TRUE);
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[68][((effectTimer) / 3) % 9], TRUE);
	}
}