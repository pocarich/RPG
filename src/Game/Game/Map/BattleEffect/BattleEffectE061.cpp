#include"../header/BattleEffectE061.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE061::BattleEffectE061(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), enemyStatus(enemyStatus)
{
	switch (direction)
	{
	case Direction::DOWN:
		this->masuPosition.y += 1;
		break;
	case Direction::LEFT:
		this->masuPosition.x -= 1;
		break;
	case Direction::RIGHT:
		this->masuPosition.x += 1;
		break;
	case Direction::UP:
		this->masuPosition.y -= 1;
		break;
	}

	for (int i = -1; i != 2; i++)for (int j = -1; j != 2; j++)
	{
		hitPositionList.push_back(Vector2<int>(this->masuPosition.x + i, this->masuPosition.y + j));
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE061::~BattleEffectE061()
{

}

void BattleEffectE061::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 61);
			}
		}
	}
	if (effectTimer == 30)
	{
		disappearFlag = true;
	}
}

void BattleEffectE061::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[39][(effectTimer / 3) % 10], TRUE);
}