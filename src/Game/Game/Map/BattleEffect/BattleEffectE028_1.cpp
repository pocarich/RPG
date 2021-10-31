#include"../header/BattleEffectE028_1.h"
#include"../header/BattleEffectE028_2.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

const double BattleEffectE028_1::speed = 2.0;
const int BattleEffectE028_1::existTime = 64;

BattleEffectE028_1::BattleEffectE028_1(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER),enemyStatus(enemyStatus)
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

	switch (direction)
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

	this->direction = direction;
}

BattleEffectE028_1::~BattleEffectE028_1()
{

}

void BattleEffectE028_1::Update()
{
	position += velocity;
	effectTimer++;
	if (effectTimer % (Define::MASU_SIZE / (int)speed) == 1)
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
			masuPosition = next;
			for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
			{
				Vector2<int> tempPos = masuPosition + Vector2<int>(i, j);
				battleEffectList.push_back(make_shared<BattleEffectE028_2>(enemyStatus, playerMap, bossMapList,objectMapList,battleEffectList, enemyMapList, sourceID, tempPos, direction, camera, mapNum));
			}
			disappearFlag = true;
			return;
		}
	}

	if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
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
		for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
		{
			Vector2<int> tempPos = masuPosition + Vector2<int>(i, j);
			battleEffectList.push_back(make_shared<BattleEffectE028_2>(enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, tempPos, direction, camera, mapNum));
		}
		disappearFlag = true;
	}

	if (effectTimer == existTime)
	{
		for (int i = -1; i < 2; i++)for (int j = -1; j < 2; j++)
		{
			Vector2<int> tempPos = masuPosition + Vector2<int>(i, j);
			battleEffectList.push_back(make_shared<BattleEffectE028_2>(enemyStatus, playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, sourceID, tempPos, direction, camera, mapNum));
		}
		disappearFlag = true;
	}
}

void BattleEffectE028_1::Draw()
{
	static const int graphKind[] = { 2,3,4,5 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[23][graphKind[(effectTimer / 3) % 4]], TRUE);
}