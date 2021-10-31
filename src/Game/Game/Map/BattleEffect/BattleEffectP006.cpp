#include"../header/BattleEffectP006.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

const int BattleEffectP006::offset = 15;

BattleEffectP006::BattleEffectP006(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),SPMAX(SPMAX)
{
	switch (playerMap->GetDirection())
	{
	case Direction::DOWN:
		this->masuPosition.y+=2;
		break;
	case Direction::LEFT:
		this->masuPosition.x-=2;
		break;
	case Direction::RIGHT:
		this->masuPosition.x+=2;
		break;
	case Direction::UP:
		this->masuPosition.y-=2;
		break;
	}
	for (int i = -1; i != 2; i++)for (int j = -1; j != 2; j++)
	{
		hitPositionList.push_back(Vector2<int>(this->masuPosition.x + i, this->masuPosition.y + j));
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectP006::~BattleEffectP006()
{

}

void BattleEffectP006::Update()
{
	effectTimer++;
	if (effectTimer <= offset * 6 && effectTimer % 20 == 1)
	{
		for (auto& pos : hitPositionList)for (auto& obj : enemyMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
			{
				obj->CauseByPlayer(sourceID, 6,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : objectMapList)
		{
			if (obj->GetCanDestroy() && pos == obj->GetMasuPosition())
			{
				obj->CauseByPlayer(sourceID, 6,SPMAX);
			}
		}
		for (auto& pos : hitPositionList)for (auto& obj : bossMapList)
		{
			Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
			if (abs(obj->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE*2 - 2.0) && abs(obj->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE*2 - 2.0))
			{
				obj->CauseByPlayer(sourceID, 6,SPMAX);
			}
		}
	}
	if (effectTimer == 127)
	{
		disappearFlag = true;
	}
}

void BattleEffectP006::Draw()
{
	static int effectKind[] = { 6,8,7,9,10,11 };
	for (int i = 0; i < 6; i++)
	{
		if (effectTimer - (offset*i) >= 0 && effectTimer - (offset*i) < 27)
		{
			DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[effectKind[i]][((effectTimer - offset*i) / 3) % 9], TRUE);
		}
	}
}