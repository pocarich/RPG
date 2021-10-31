#include"../header/BattleEffectE087.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

const double BattleEffectE087::speed = 1.0;
const int BattleEffectE087::existTime = 256;
const int BattleEffectE087::hitInterval = 10;

BattleEffectE087::BattleEffectE087(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
{
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

BattleEffectE087::~BattleEffectE087()
{

}

void BattleEffectE087::Update()
{
	if (effectTimer % (Define::MASU_SIZE / (int)speed) == 0)
	{
		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
		Vector2<int> next1, next2;
		Direction nextDirection1, nextDirection2;

		if (abs(diff.x) <= abs(diff.y))
		{
			if (diff.y > 0)
			{
				next1 = masuPosition + Vector2<int>(0, 1);
				nextDirection1 = Direction::DOWN;
			}
			else
			{
				next1 = masuPosition + Vector2<int>(0, -1);
				nextDirection1 = Direction::UP;
			}
			if (diff.x > 0)
			{
				next2 = masuPosition + Vector2<int>(1, 0);
				nextDirection2 = Direction::RIGHT;
			}
			else
			{
				next2 = masuPosition + Vector2<int>(-1, 0);
				nextDirection2 = Direction::LEFT;
			}
		}
		else
		{
			if (diff.y > 0)
			{
				next2 = masuPosition + Vector2<int>(0, 1);
				nextDirection2 = Direction::DOWN;
			}
			else
			{
				next2 = masuPosition + Vector2<int>(0, -1);
				nextDirection2 = Direction::UP;
			}
			if (diff.x > 0)
			{
				next1 = masuPosition + Vector2<int>(1, 0);
				nextDirection1 = Direction::RIGHT;
			}
			else
			{
				next1 = masuPosition + Vector2<int>(-1, 0);
				nextDirection1 = Direction::LEFT;
			}
		}

		if (CanMoveToNextPosition(next1,nextDirection1))
		{
			direction = nextDirection1;
		}
		else
		{
			direction = nextDirection2;
		}

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
			masuPosition = next;
		}
		else
		{
			disappearFlag = true;
			return;
		}
	}

	position += velocity;
	effectTimer++;

	if (effectTimer%hitInterval == 1)
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE * 2 - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE * 2 - 2.0))
		{
			playerMap->CauseByBoss(bossStatus, direction, sourceID, 87);
		}
	}

	if (effectTimer == existTime)
	{
		disappearFlag = true;
	}
}

void BattleEffectE087::Draw()
{
	static const int graphKind[] = { 2,3,4,5 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[49][graphKind[(effectTimer / 3) % 4]], TRUE);
}