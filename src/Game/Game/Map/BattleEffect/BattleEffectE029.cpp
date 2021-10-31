#include"../header/BattleEffectE029.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE029::BattleEffectE029(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), enemyStatus(enemyStatus)
{
	switch (direction)
	{
	case Direction::DOWN:
		this->masuPosition.y++;
		break;
	case Direction::LEFT:
		this->masuPosition.x--;
		break;
	case Direction::RIGHT:
		this->masuPosition.x++;
		break;
	case Direction::UP:
		this->masuPosition.y--;
		break;
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE029::~BattleEffectE029()
{

}

void BattleEffectE029::Update()
{
	effectTimer++;
	if (effectTimer == 1 || effectTimer == 28)
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 11);
		}
	}
	if (effectTimer == 54)
	{
		disappearFlag = true;
	}
}

void BattleEffectE029::Draw()
{
	if (effectTimer < 27)
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[33][(effectTimer / 3) % 9], TRUE);
	}
	if (0 <= (effectTimer - 27))
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[34][(effectTimer / 3) % 9], TRUE);
	}
}