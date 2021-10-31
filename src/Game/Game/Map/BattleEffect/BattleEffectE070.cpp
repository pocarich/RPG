#include"../header/BattleEffectE070.h"
#include"../header/PlayerMap.h"
#include"../header/EnemyMap.h"

const double BattleEffectE070::speed = 4.0;
const int BattleEffectE070::existTime = 72;

BattleEffectE070::BattleEffectE070(EnemyStatus enemyStatus, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<BattleEffectPtr>& battleEffectList, list<EnemyMapPtr>& enemyMapList, int sourceID, Vector2<int> masuPosition, Direction direction, Vector2<double>&camera, int& mapNum) :BattleEffect(playerMap, bossMapList, objectMapList, battleEffectList, enemyMapList, ObjectType::PLAYER, sourceID, masuPosition, direction, camera, mapNum, TargetType::PLAYER), enemyStatus(enemyStatus)
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
	for (int i = -1; i != 2; i++)for (int j = -1; j != 2; j++)
	{
		if (i != 0 || j != 0)
		{
			hitPositionList.push_back(Vector2<int>(this->masuPosition.x + i, this->masuPosition.y + j));
		}
	}

	position = Vector2<double>(this->masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, this->masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);

}

BattleEffectE070::~BattleEffectE070()
{

}

void BattleEffectE070::Update()
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
			playerMap->CauseByEnemy(enemyStatus, direction, sourceID, 70);
			disappearFlag = true;
		}
	}

	if (effectTimer == existTime)
	{
		disappearFlag = true;
	}
}

void BattleEffectE070::Draw()
{
	static const int graphKind[] = { 5,6,7,8,9 };
	DrawRotaGraphF((float)position.x - camera.x, (float)position.y - camera.y, 1.0, 0.0, graph[54][graphKind[(effectTimer / 3) % 5]], TRUE);
}