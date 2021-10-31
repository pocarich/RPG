#include"../header/BattleEffectE117_2.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

const double BattleEffectE117_2::speed = 2.0;
const int BattleEffectE117_2::existTime = 600;
const int BattleEffectE117_2::hitInterval = 20;

BattleEffectE117_2::BattleEffectE117_2(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
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

BattleEffectE117_2::~BattleEffectE117_2()
{

}

void BattleEffectE117_2::Update()
{
	if (effectTimer % (Define::MASU_SIZE / (int)speed) == 0)
	{
		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
		Vector2<int> next1;
		Direction nextDirection1;

		switch (GetRand(100) % 4)
		{
		case 0:
			next1 = masuPosition + Vector2<int>(0, 1);
			nextDirection1 = Direction::DOWN;
			break;
		case 1:
			next1 = masuPosition + Vector2<int>(0, -1);
			nextDirection1 = Direction::UP;
			break;
		case 2:
			next1 = masuPosition + Vector2<int>(1, 0);
			nextDirection1 = Direction::RIGHT;
			break;
		case 3:
			next1 = masuPosition + Vector2<int>(-1, 0);
			nextDirection1 = Direction::LEFT;
			break;
		}

		if (CanMoveToNextPosition(next1, nextDirection1))
		{
			direction = nextDirection1;
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
		}
		else
		{
			return;
		}
	}

	position += velocity;
	effectTimer++;

	if (effectTimer%hitInterval == 1)
	{
		if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE * 2 - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE * 2 - 2.0))
		{
			playerMap->CauseByBoss(bossStatus, direction, sourceID, 117);
		}
	}

	if (effectTimer == existTime)
	{
		disappearFlag = true;
	}
}

void BattleEffectE117_2::Draw()
{
	static const int graphKind[] = { 2,3,4,5 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[74][graphKind[(effectTimer / 3) % 4]], TRUE);
}