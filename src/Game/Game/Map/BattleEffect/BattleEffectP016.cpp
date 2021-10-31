#include"../header/BattleEffectP016.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/MapInfoList.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

BattleEffectP016::BattleEffectP016(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, int count,bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY), count(count),SPMAX(SPMAX)
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

BattleEffectP016::~BattleEffectP016()
{

}

void BattleEffectP016::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& obj : enemyMapList)
		{
			if (abs(obj->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(obj->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				obj->CauseByPlayer(sourceID, 16,SPMAX);
			}
		}
		for (auto& obj : objectMapList)
		{
			if (obj->GetCanDestroy() && masuPosition == obj->GetMasuPosition())
			{
				obj->CauseByPlayer(sourceID, 16,SPMAX);
			}
		}
		for (auto& obj : bossMapList)
		{
			if (abs(obj->GetPosition().x - position.x) < ((double)Define::MASU_SIZE*2 - 2.0) && abs(obj->GetPosition().y - position.y) < ((double)Define::MASU_SIZE*2 - 2.0))
			{
				obj->CauseByPlayer(sourceID, 16,SPMAX);
			}
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
			battleEffectList.push_back(make_shared<BattleEffectP016>(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, masuPosition, direction, camera, mapNum, count + 1,SPMAX));
		}
	}

	if (effectTimer == 24)
	{
		disappearFlag = true;
	}
}

void BattleEffectP016::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - 10 - camera.y, 1.0, 0.0, graph[22][(effectTimer / 3) % 8], TRUE);
}