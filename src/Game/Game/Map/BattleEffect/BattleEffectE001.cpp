#include"../header/BattleEffectE001.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

BattleEffectE001::BattleEffectE001(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::ENEMY, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER),enemyStatus(enemyStatus)
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

BattleEffectE001::~BattleEffectE001()
{

}

void BattleEffectE001::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			playerMap->CauseByEnemy(enemyStatus,direction, sourceID, 1);
		}
	}
	if (effectTimer == 30)
	{
		disappearFlag = true;
	}
}

void BattleEffectE001::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[29][(effectTimer / 3) % 10], TRUE);
}