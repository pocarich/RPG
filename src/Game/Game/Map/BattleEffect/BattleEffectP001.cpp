#include"../header/BattleEffectP001.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

BattleEffectP001::BattleEffectP001(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum, bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),SPMAX(SPMAX)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	hitPositionList.push_back(Vector2<int>(masuPosition.x + 1, masuPosition.y));
	hitPositionList.push_back(Vector2<int>(masuPosition.x - 1, masuPosition.y));
	hitPositionList.push_back(Vector2<int>(masuPosition.x, masuPosition.y + 1));
	hitPositionList.push_back(Vector2<int>(masuPosition.x, masuPosition.y - 1));
	hitPositionList.push_back(Vector2<int>(masuPosition.x + 1, masuPosition.y + 1));
	hitPositionList.push_back(Vector2<int>(masuPosition.x + 1, masuPosition.y - 1));
	hitPositionList.push_back(Vector2<int>(masuPosition.x - 1, masuPosition.y + 1));
	hitPositionList.push_back(Vector2<int>(masuPosition.x - 1, masuPosition.y - 1));
}

BattleEffectP001::~BattleEffectP001()
{

}

void BattleEffectP001::Update()
{
	effectTimer++;
	if (effectTimer == 1)
	{
		for(auto& pos:hitPositionList)for (auto& obj : enemyMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				obj->CauseByPlayer(sourceID, 1,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : objectMapList)
		{
			if (obj->GetCanDestroy()&&pos == obj->GetMasuPosition())
			{
				obj->CauseByPlayer(sourceID, 1,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : bossMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE*2 - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE*2 - 2.0))
			{
				obj->CauseByPlayer(sourceID, 1, SPMAX);
			}
		}
	}
	if (effectTimer == 30)
	{
		disappearFlag = true;
	}
}

void BattleEffectP001::Draw()
{
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[2][(effectTimer / 3) % 10], TRUE);
}