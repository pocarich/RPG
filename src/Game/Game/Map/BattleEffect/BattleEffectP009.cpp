#include"../header/BattleEffectP009.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

const int BattleEffectP009::distance = 5;

BattleEffectP009::BattleEffectP009(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),SPMAX(SPMAX)
{
	switch (direction)
	{
	case Direction::DOWN:
		this->masuPosition.y+=distance;
		break;
	case Direction::LEFT:
		this->masuPosition.x-=distance;
		break;
	case Direction::RIGHT:
		this->masuPosition.x+=distance;
		break;
	case Direction::UP:
		this->masuPosition.y-=distance;
		break;
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	
	for (int i = -2; i != 3; i++)for (int j = -2; j != 3; j++)
	{
		if (!((i == -2 && j == -2) || (i == -2 && j == 2) || (i == 2 && j == -2) || (i == 2 && j == 2)))
		{
			hitPositionList.push_back(Vector2<int>(this->masuPosition.x + i, this->masuPosition.y + j));
		}
	}
}

BattleEffectP009::~BattleEffectP009()
{

}

void BattleEffectP009::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)for (auto& obj : enemyMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				obj->CauseByPlayer(sourceID, 9,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : objectMapList)
		{
			if (obj->GetCanDestroy() && pos == obj->GetMasuPosition())
			{
				obj->CauseByPlayer(sourceID, 9,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : bossMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE*2 - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE*2 - 2.0))
			{
				obj->CauseByPlayer(sourceID, 9,SPMAX);
			}
		}
	}
	if (effectTimer == 32)
	{
		disappearFlag = true;
	}
}

void BattleEffectP009::Draw()
{
	for (auto& pos : hitPositionList)
	{
		Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
		DrawRotaGraphF((float)tempPos.x - camera.x, (float)tempPos.y - camera.y, 1.0, 0.0, graph[15][(effectTimer / 4) % 8], TRUE);
	}
}