#include"../header/BattleEffectE077_2.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE077_2::BattleEffectE077_2(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), enemyStatus(enemyStatus)
{
	for (int i = -2; i < 3; i++)for (int j = -2; j < 3; j++)
	{
		attackPositionList.push_back(this->masuPosition + Vector2<int>(i, j));
	}
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectE077_2::~BattleEffectE077_2()
{

}

void BattleEffectE077_2::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : attackPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 77);
			}
		}
	}
	if (effectTimer == 24)
	{
		disappearFlag = true;
	}
}

void BattleEffectE077_2::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[58][(effectTimer / 3) % 8], TRUE);
}