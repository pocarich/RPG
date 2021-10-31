#include"../header/BattleEffectP010.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

BattleEffectP010::BattleEffectP010(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),SPMAX(SPMAX)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	for (int i = -2; i != 3; i++)for (int j = -2; j != 3; j++)
	{
		hitPositionList.push_back(Vector2<int>(this->masuPosition.x + i, this->masuPosition.y + j));
	}

	drawPositionList.push_back(Vector2<double>(position.x - 36, position.y - 36));
	drawPositionList.push_back(Vector2<double>(position.x - 36, position.y + 36));
	drawPositionList.push_back(Vector2<double>(position.x + 36, position.y - 36));
	drawPositionList.push_back(Vector2<double>(position.x + 36, position.y + 36));
}

BattleEffectP010::~BattleEffectP010()
{

}

void BattleEffectP010::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for (auto& pos : hitPositionList)for (auto& obj : enemyMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				obj->CauseByPlayer(sourceID, 10,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : objectMapList)
		{
			if (obj->GetCanDestroy() && pos == obj->GetMasuPosition())
			{
				obj->CauseByPlayer(sourceID, 10,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : bossMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE*2 - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE*2 - 2.0))
			{
				obj->CauseByPlayer(sourceID, 10,SPMAX);
			}
		}
	}
	if (effectTimer == 24)
	{
		disappearFlag = true;
	}
}

void BattleEffectP010::Draw()
{
	for (auto& pos : drawPositionList)
	{
		DrawRotaGraphF((float)pos.x - camera.x, (float)pos.y - camera.y, 1.0, 0.0, graph[16][(effectTimer / 3) % 8], TRUE);
	}
}