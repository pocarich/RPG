#include"../header/BattleEffectP002.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

BattleEffectP002::BattleEffectP002(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),SPMAX(SPMAX)
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

BattleEffectP002::~BattleEffectP002()
{

}

void BattleEffectP002::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& obj : enemyMapList)
		{
			if (abs(obj->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(obj->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				obj->CauseByPlayer(sourceID, 2,SPMAX);
			}
		}
		for (auto& obj : objectMapList)
		{
			if (obj->GetCanDestroy() && masuPosition == obj->GetMasuPosition())
			{
				obj->CauseByPlayer(sourceID, 2,SPMAX);
			}
		}
		for (auto& obj : bossMapList)
		{
			if (abs(obj->GetPosition().x - position.x) < ((double)Define::MASU_SIZE*2 - 2.0) && abs(obj->GetPosition().y - position.y) < ((double)Define::MASU_SIZE*2 - 2.0))
			{
				obj->CauseByPlayer(sourceID, 2,SPMAX);
			}
		}
	}
	if (effectTimer == 14)
	{
		disappearFlag = true;
	}
}

void BattleEffectP002::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[3][(effectTimer / 3) % 5], TRUE);
}