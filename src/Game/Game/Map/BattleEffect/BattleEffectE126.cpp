#include"../header/BattleEffectE126.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

const double BattleEffectE126::speed = 4.0;
const int BattleEffectE126::existTime = 1600;
const int BattleEffectE126::hitInterval = 10;

BattleEffectE126::BattleEffectE126(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
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

	subMoveCounter = 0;
	subLevel = 0;
	subState = 0;
	this->direction = direction;
	hitPositionList.push_back(this->masuPosition);
	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	for (int i = -1; i != 2; i++)for (int j = -1; j != 2; j++)
	{
		if (i != 0 || j != 0)
		{
			hitPositionList.push_back(Vector2<int>(this->masuPosition.x + i, this->masuPosition.y + j));
		}
	}
}

BattleEffectE126::~BattleEffectE126()
{

}

void BattleEffectE126::Update()
{
	static const int nextDir[] = { 2,0,3,1 };

	if (effectTimer % (Define::MASU_SIZE / (int)speed) == 0)
	{
		subMoveCounter++;
		if (subMoveCounter == (1 * subLevel + 1))
		{
			direction = (Direction)nextDir[(int)direction];
			subState++;
			if (subState == 2)
			{
				subState = 0;
				subLevel++;
			}
			subMoveCounter = 0;
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

		Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
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
		if (CanMoveToNextPosition(next, direction))
		{
			switch (direction)
			{
			case Direction::DOWN:
				for (int i = 0; i != hitPositionList.size(); i++)
				{
					hitPositionList[i] = hitPositionList[i] + Vector2<int>((int)Vector2<double>::DOWN.x, (int)Vector2<double>::DOWN.y);
				}
				break;
			case Direction::LEFT:
				for (int i = 0; i != hitPositionList.size(); i++)
				{
					hitPositionList[i] = hitPositionList[i] + Vector2<int>((int)Vector2<double>::LEFT.x, (int)Vector2<double>::LEFT.y);
				}				break;
			case Direction::RIGHT:
				for (int i = 0; i != hitPositionList.size(); i++)
				{
					hitPositionList[i] = hitPositionList[i] + Vector2<int>((int)Vector2<double>::RIGHT.x, (int)Vector2<double>::RIGHT.y);
				}				break;
			case Direction::UP:
				for (int i = 0; i != hitPositionList.size(); i++)
				{
					hitPositionList[i] = hitPositionList[i] + Vector2<int>((int)Vector2<double>::UP.x, (int)Vector2<double>::UP.y);
				}				break;
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
			playerMap->CauseByBoss(bossStatus, direction, sourceID, 126);
		}
	}

	if (effectTimer == existTime)
	{
		disappearFlag = true;
	}
}

void BattleEffectE126::Draw()
{
	static const int graphKind[] = { 2,3,4,5 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[49][graphKind[(effectTimer / 3) % 4]], TRUE);
}