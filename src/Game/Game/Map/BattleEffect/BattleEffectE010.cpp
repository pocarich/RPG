#include"../header/BattleEffectE010.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

const double BattleEffectE010::speed = 2.0;
const int BattleEffectE010::existTime = 48;

BattleEffectE010::BattleEffectE010(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction,EightDirection eightDirection, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), enemyStatus(enemyStatus),eightDirection(eightDirection)
{
	switch (eightDirection)
	{
	case EightDirection::UP:
		velocity = Vector2<double>::UP*speed;
		break;
	case EightDirection::UPRIGHT:
		velocity = Vector2<double>(1.0, -1.0).unit()*speed;
		break;
	case EightDirection::RIGHT:
		velocity = Vector2<double>::RIGHT*speed;
		break;
	case EightDirection::DOWNRIGHT:
		velocity = Vector2<double>(1.0, 1.0).unit()*speed;
		break;
	case EightDirection::DOWN:
		velocity = Vector2<double>::DOWN*speed;
		break;
	case EightDirection::DOWNLEFT:
		velocity = Vector2<double>(-1.0, 1.0).unit()*speed;
		break;
	case EightDirection::LEFT:
		velocity = Vector2<double>::LEFT*speed;
		break;
	case EightDirection::UPLEFT:
		velocity = Vector2<double>(-1.0, -1.0).unit()*speed;
		break;
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE010::~BattleEffectE010()
{

}

void BattleEffectE010::Update()
{
	int length;
	position += velocity;

	effectTimer++;

	switch (eightDirection)
	{
	case EightDirection::UP:
		length = Define::MASU_SIZE;
		break;
	case EightDirection::UPRIGHT:
		length = Define::MASU_SIZE*sqrt(2);
		break;
	case EightDirection::RIGHT:
		length = Define::MASU_SIZE;
		break;
	case EightDirection::DOWNRIGHT:
		length = Define::MASU_SIZE*sqrt(2);
		break;
	case EightDirection::DOWN:
		length = Define::MASU_SIZE;
		break;
	case EightDirection::DOWNLEFT:
		length = Define::MASU_SIZE*sqrt(2);
		break;
	case EightDirection::LEFT:
		length = Define::MASU_SIZE;
		break;
	case EightDirection::UPLEFT:
		length = Define::MASU_SIZE*sqrt(2);
		break;
	}

	if (effectTimer % (length / (int)speed) == 1)
	{
		Vector2<int> next;
		Direction nextDirection1, nextDirection2;
		switch (eightDirection)
		{
		case EightDirection::UP:
			next = masuPosition + Vector2<int>(0, -1);
			nextDirection1 = nextDirection2 = Direction::UP;
			break;
		case EightDirection::UPRIGHT:
			next = masuPosition + Vector2<int>(1, -1);
			nextDirection1 = Direction::UP;
			nextDirection2 = Direction::RIGHT;
			break;
		case EightDirection::RIGHT:
			next = masuPosition + Vector2<int>(1, 0);
			nextDirection1 = nextDirection2 = Direction::RIGHT;
			break;
		case EightDirection::DOWNRIGHT:
			next = masuPosition + Vector2<int>(1, 1);
			nextDirection1 = Direction::DOWN;
			nextDirection2 = Direction::RIGHT;
			break;
		case EightDirection::DOWN:
			next = masuPosition + Vector2<int>(0, 1);
			nextDirection1 = nextDirection2 = Direction::DOWN;
			break;
		case EightDirection::DOWNLEFT:
			next = masuPosition + Vector2<int>(-1, 1);
			nextDirection1 = Direction::DOWN;
			nextDirection2 = Direction::LEFT;
			break;
		case EightDirection::LEFT:
			next = masuPosition + Vector2<int>(-1, 0);
			nextDirection1 = nextDirection2 = Direction::LEFT;
			break;
		case EightDirection::UPLEFT:
			next = masuPosition + Vector2<int>(-1, -1);
			nextDirection1 = Direction::UP;
			nextDirection2 = Direction::LEFT;
			break;
		}
	
		if (CanMoveToNextPosition(next, nextDirection1) && CanMoveToNextPosition(next, nextDirection2))
		{
			masuPosition = next;
		}
		else
		{
			disappearFlag = true;
			return;
		}
	}


	if (abs(playerMap->GetPosition().x - position.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - position.y) < ((double)Define::MASU_SIZE - 2.0))
	{
		playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 10);
		disappearFlag = true;
	}

	if (effectTimer == existTime)
	{
		disappearFlag = true;
	}
}

void BattleEffectE010::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	static const int graphKind[] = { 3,4,5,6 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[32][graphKind[(effectTimer / 3) % 4]], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}