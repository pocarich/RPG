#include"../header/BattleEffectE121.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

const double BattleEffectE121::speed = 4.0;
const int BattleEffectE121::existTime = 800;

BattleEffectE121::BattleEffectE121(BossStatus bossStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), bossStatus(bossStatus)
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

	hitPositionList.push_back(this->masuPosition);

	changeDirectionCounter = 0;

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
}

BattleEffectE121::~BattleEffectE121()
{

}

void BattleEffectE121::Update()
{
	position += velocity;

	effectTimer++;

	if (effectTimer % (Define::MASU_SIZE / (int)speed) == ((Define::MASU_SIZE / (int)speed)-1))
	{
		if (changeDirectionCounter < 2)
		{
			Vector2<int> diff = playerMap->GetMasuPosition() - masuPosition;
			switch (direction)
			{
			case Direction::DOWN:
				if (diff.y == 0)
				{
					if (diff.x < 0)
					{
						direction = Direction::LEFT;
						velocity = Vector2<double>::LEFT*speed;

					}
					else
					{
						direction = Direction::RIGHT;
						velocity = Vector2<double>::RIGHT*speed;

					}
					changeDirectionCounter++;

				}
				break;
			case Direction::UP:
				if (diff.y == 0)
				{
					if (diff.x < 0)
					{
						direction = Direction::LEFT;
						velocity = Vector2<double>::LEFT*speed;
					}
					else
					{
						direction = Direction::RIGHT;
						velocity = Vector2<double>::RIGHT*speed;

					}
					changeDirectionCounter++;

				}
				break;
			case Direction::LEFT:
				if (diff.x == 0)
				{
					if (diff.y < 0)
					{
						direction = Direction::UP;
						velocity = Vector2<double>::UP*speed;
					}
					else
					{
						direction = Direction::DOWN;
						velocity = Vector2<double>::DOWN*speed;
					}
					changeDirectionCounter++;

				}
				break;
			case Direction::RIGHT:
				if (diff.x == 0)
				{
					if (diff.y < 0)
					{
						direction = Direction::UP;
						velocity = Vector2<double>::UP*speed;
					}
					else
					{
						direction = Direction::DOWN;
						velocity = Vector2<double>::DOWN*speed;
					}
					changeDirectionCounter++;

				}
				break;
			}
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
		if (CanMoveToNextPosition(next, direction))
		{
			masuPosition = next;
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
		}
		else
		{
			disappearFlag = true;
			return;
		}
	}

	for (auto& pos : hitPositionList)
	{
		Vector2<double> tempPos = Vector2<double>(pos.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, pos.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
		if (abs(playerMap->GetPosition().x - tempPos.x) < ((double)Define::MASU_SIZE - 2.0) && abs(playerMap->GetPosition().y - tempPos.y) < ((double)Define::MASU_SIZE - 2.0))
		{
			playerMap->CauseByBoss(bossStatus, direction, sourceID, 121);
			disappearFlag = true;
		}
	}

	if (effectTimer == existTime)
	{
		disappearFlag = true;
	}
}

void BattleEffectE121::Draw()
{
	static const int graphKind[] = { 5,6,7,8,9 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[54][graphKind[(effectTimer / 3) % 5]], TRUE);
}