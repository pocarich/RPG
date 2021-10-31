#include"../header/BattleEffectE102.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE102::BattleEffectE102(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
	for (int i = -10; i < 11; i++)for (int j = -1; j < 2; j++)
	{
		hitPositionList.push_back(masuPosition + Vector2<int>(i, j));
	}
	for (int i = -10; i < 11; i++)for (int j = -1; j < 2; j++)
	{
		hitPositionList.push_back(masuPosition + Vector2<int>(j, i));
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE102::~BattleEffectE102()
{

}

void BattleEffectE102::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByBoss(bossStatus, direction, sourceID, 102);
			}
		}
	}
	if (effectTimer == 27)
	{
		disappearFlag = true;
	}
}

void BattleEffectE102::Draw()
{
	if (effectTimer < 27)
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[65][((effectTimer) / 3) % 9], TRUE);
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[66][((effectTimer) / 3) % 9], TRUE);
	}
}