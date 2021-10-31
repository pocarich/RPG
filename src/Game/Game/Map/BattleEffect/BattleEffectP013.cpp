#include"../header/BattleEffectP013.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

BattleEffectP013::BattleEffectP013(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),SPMAX(SPMAX)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	for (int i = -3; i != 4; i++)for (int j = -3; j != 4; j++)
	{
		hitPositionList.push_back(Vector2<int>(this->masuPosition.x + i, this->masuPosition.y + j));
	}

	drawPositionList.push_back(Vector2<double>(position.x - 50, position.y - 50));
	drawPositionList.push_back(Vector2<double>(position.x - 50, position.y + 50));
	drawPositionList.push_back(Vector2<double>(position.x + 50, position.y - 50));
	drawPositionList.push_back(Vector2<double>(position.x + 50, position.y + 50));
}

BattleEffectP013::~BattleEffectP013()
{

}

void BattleEffectP013::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)for (auto& obj : enemyMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				obj->CauseByPlayer(sourceID, 13,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : objectMapList)
		{
			if (obj->GetCanDestroy() && pos == obj->GetMasuPosition())
			{
				obj->CauseByPlayer(sourceID, 13,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : bossMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE*2 - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE*2 - 2.0))
			{
				obj->CauseByPlayer(sourceID, 13,SPMAX);
			}
		}
	}
	if (effectTimer == 24)
	{
		disappearFlag = true;
	}
}

void BattleEffectP013::Draw()
{
	for (auto& pos : drawPositionList)
	{
		DrawRotaGraphF((float)pos.x - camera.x, (float)pos.y - camera.y, 1.0, 0.0, graph[19][(effectTimer / 3) % 8], TRUE);
	}
}