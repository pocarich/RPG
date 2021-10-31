#include"../header/BattleEffectE081.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE081::BattleEffectE081(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), enemyStatus(enemyStatus)
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

BattleEffectE081::~BattleEffectE081()
{

}

void BattleEffectE081::Update()
{
	effectTimer++;
	if (effectTimer %interval == 1 && effectTimer <= (interval * 2 + 1))
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 81);
		}
	}
	if (effectTimer == (interval * 2 + 30))
	{
		disappearFlag = true;
	}
}

void BattleEffectE081::Draw()
{
	if (effectTimer <= 24)
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[28][(effectTimer / 3) % 10], TRUE);
	}

	if (0 <= (effectTimer - interval) && (effectTimer - interval) <= 24)
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[28][((effectTimer - interval) / 3) % 10], TRUE);
	}

	if (0 <= (effectTimer - interval * 2) && (effectTimer - interval * 2) <= 30)
	{
		DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[28][((effectTimer - interval * 2) / 3) % 10], TRUE);
	}
}