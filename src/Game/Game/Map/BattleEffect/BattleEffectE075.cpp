#include"../header/BattleEffectE075.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE075::BattleEffectE075(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), enemyStatus(enemyStatus)
{
	for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
	{
		hitPositionList.push_back(this->masuPosition + Vector2<int>(i, j));
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectE075::~BattleEffectE075()
{

}

void BattleEffectE075::Update()
{
	effectTimer++;
	if (effectTimer == 1 || effectTimer == 28)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 75);
			}
		}
	}
	if (effectTimer == 54)
	{
		disappearFlag = true;
	}
}

void BattleEffectE075::Draw()
{
	if (effectTimer < 27)
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[44][(effectTimer / 3) % 9], TRUE);
	}
	if (0 <= (effectTimer - 27))
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[45][(effectTimer / 3) % 9], TRUE);
	}
}