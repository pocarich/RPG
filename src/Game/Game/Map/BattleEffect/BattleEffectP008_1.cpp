#include"../header/BattleEffectP008_1.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"
#include"../header/BattleEffectP008_2.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

const double BattleEffectP008_1::speed = 8.0;
const int BattleEffectP008_1::existTime = 40;

BattleEffectP008_1::BattleEffectP008_1(PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum,bool SPMAX) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::ENEMY),SPMAX(SPMAX)
{
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	this->direction = playerMap->GetDirection();

	switch (playerMap->GetDirection())
	{
	case Direction::DOWN:
		velocity = Vector2<double>::DOWN*speed;
		break;
	case Direction::LEFT:
		velocity = Vector2<double>::LEFT*speed;
		break;
	case Direction::RIGHT:
		velocity = Vector2<double>::RIGHT*speed;
		break;
	case Direction::UP:
		velocity = Vector2<double>::UP*speed;
		break;
	}
}

BattleEffectP008_1::~BattleEffectP008_1()
{

}

void BattleEffectP008_1::Update()
{
	position += velocity;

	effectTimer++;

	if (effectTimer % (Define::MASU_SIZE / (int)speed) == 2)
	{
		Vector2<int> next;
		switch (direction)
		{
		case Direction::DOWN:
			next = masuPosition + Vector2<int>((int)Vector2<double>::DOWN.x, (int)Vector2<double>::DOWN.y);
			break;
		case Direction::LEFT:
			next = masuPosition + Vector2<int>((int)Vector2<double>::LEFT.x, (int)Vector2<double>::LEFT.y);
			break;
		case Direction::RIGHT:
			next = masuPosition + Vector2<int>((int)Vector2<double>::RIGHT.x, (int)Vector2<double>::RIGHT.y);
			break;
		case Direction::UP:
			next = masuPosition + Vector2<int>((int)Vector2<double>::UP.x, (int)Vector2<double>::UP.y);
			break;
		}
		if (CanMoveToNextPosition(next,direction))
		{
			masuPosition = next;
		}
		else
		{
			disappearFlag = true;
			return;
		}
	}

	for (auto& obj : enemyMapList)
	{
		if (abs(obj->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(obj->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			Vector2<int> next;
			switch (direction)
			{
			case Direction::DOWN:
				next = masuPosition + Vector2<int>((int)Vector2<double>::DOWN.x, (int)Vector2<double>::DOWN.y);
				break;
			case Direction::LEFT:
				next = masuPosition + Vector2<int>((int)Vector2<double>::LEFT.x, (int)Vector2<double>::LEFT.y);
				break;
			case Direction::RIGHT:
				next = masuPosition + Vector2<int>((int)Vector2<double>::RIGHT.x, (int)Vector2<double>::RIGHT.y);
				break;
			case Direction::UP:
				next = masuPosition + Vector2<int>((int)Vector2<double>::UP.x, (int)Vector2<double>::UP.y);
				break;
			}
			masuPosition = next;
			battleEffectList.push_back(make_shared<BattleEffectP008_2>(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, masuPosition, direction, camera, mapNum,SPMAX));
			disappearFlag = true;
		}
	}
	for (auto& obj : objectMapList)
	{
		if (obj->GetCanDestroy() && masuPosition == obj->GetMasuPosition())
		{
			Vector2<int> next;
			switch (direction)
			{
			case Direction::DOWN:
				next = masuPosition + Vector2<int>((int)Vector2<double>::DOWN.x, (int)Vector2<double>::DOWN.y);
				break;
			case Direction::LEFT:
				next = masuPosition + Vector2<int>((int)Vector2<double>::LEFT.x, (int)Vector2<double>::LEFT.y);
				break;
			case Direction::RIGHT:
				next = masuPosition + Vector2<int>((int)Vector2<double>::RIGHT.x, (int)Vector2<double>::RIGHT.y);
				break;
			case Direction::UP:
				next = masuPosition + Vector2<int>((int)Vector2<double>::UP.x, (int)Vector2<double>::UP.y);
				break;
			}
			masuPosition = next;
			battleEffectList.push_back(make_shared<BattleEffectP008_2>(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, masuPosition, direction, camera, mapNum,SPMAX));
			disappearFlag = true;
		}
	}
	for (auto& obj : bossMapList)
	{
		if (abs(obj->GetPosition().x - position.x) < ((double)Define::MASU_SIZE*2 - 2.0) && abs(obj->GetPosition().y - position.y) < ((double)Define::MASU_SIZE*2 - 2.0))
		{
			Vector2<int> next;
			switch (direction)
			{
			case Direction::DOWN:
				next = masuPosition + Vector2<int>((int)Vector2<double>::DOWN.x, (int)Vector2<double>::DOWN.y);
				break;
			case Direction::LEFT:
				next = masuPosition + Vector2<int>((int)Vector2<double>::LEFT.x, (int)Vector2<double>::LEFT.y);
				break;
			case Direction::RIGHT:
				next = masuPosition + Vector2<int>((int)Vector2<double>::RIGHT.x, (int)Vector2<double>::RIGHT.y);
				break;
			case Direction::UP:
				next = masuPosition + Vector2<int>((int)Vector2<double>::UP.x, (int)Vector2<double>::UP.y);
				break;
			}
			masuPosition = next;
			battleEffectList.push_back(make_shared<BattleEffectP008_2>(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, masuPosition, direction, camera, mapNum,SPMAX));
			disappearFlag = true;
		}
	}

	if (effectTimer == existTime)
	{
		disappearFlag = true;
	}
}

void BattleEffectP008_1::Draw()
{
	static const int graphKind[] = { 2,3,4,5 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[13][graphKind[(effectTimer / 3) % 4]], TRUE);
}

