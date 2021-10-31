#include"../header/BattleEffectP005.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

BattleEffectP005::BattleEffectP005(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),SPMAX(SPMAX)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	
	for (int i = -2; i != 3; i++)for (int j = -2; j != 3; j++)
	{
		if (i == 0 && j == 0)
		{
			continue;
		}
		hitPositionList.push_back(Vector2<int>(masuPosition.x + i, masuPosition.y + j));
	}
}

BattleEffectP005::~BattleEffectP005()
{

}

void BattleEffectP005::Update()
{
	effectTimer++;
	if (effectTimer % 10 == 1)
	{
		for (auto& pos : hitPositionList)for (auto& obj : enemyMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				obj->CauseByPlayer(sourceID, 5,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : objectMapList)
		{
			if (obj->GetCanDestroy() && pos == obj->GetMasuPosition())
			{
				obj->CauseByPlayer(sourceID, 5,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : bossMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE*2 - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE*2 - 2.0))
			{
				obj->CauseByPlayer(sourceID, 5,SPMAX);
			}
		}
	}
	if (effectTimer == 72)
	{
		disappearFlag = true;
	}
}

void BattleEffectP005::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[5][(effectTimer / 3) % 24], TRUE);
}