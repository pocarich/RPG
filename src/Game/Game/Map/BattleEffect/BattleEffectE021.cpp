#include"../header/BattleEffectE021.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/MapInfoList.h"

BattleEffectE021::BattleEffectE021(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,int count) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER),enemyStatus(enemyStatus),count(count)
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

BattleEffectE021::~BattleEffectE021()
{

}

void BattleEffectE021::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			playerMap->CauseByEnemy(enemyStatus,direction, sourceID, 21);
		}
	}

	if (effectTimer == createNextEffectTime&&count != effectMax)
	{
		bool canCreate = true;

		switch (direction)
		{
		case Direction::DOWN:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y + 1][masuPosition.x];
			break;
		case Direction::LEFT:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y][masuPosition.x - 1];
			break;
		case Direction::RIGHT:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y][masuPosition.x + 1];
			break;
		case Direction::UP:
			canCreate = MapInfoList::GetMapInfoList()[mapNum].canThrough[masuPosition.y - 1][masuPosition.x];
			break;
		}

		if (canCreate)
		{
			battleEffectList.push_back(make_shared<BattleEffectE021>(enemyStatus,playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, masuPosition, direction, camera, mapNum, count + 1));
		}
	}

	if (effectTimer == 24)
	{
		disappearFlag = true;
	}
}

void BattleEffectE021::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[38][(effectTimer / 3) % 8], TRUE);
}