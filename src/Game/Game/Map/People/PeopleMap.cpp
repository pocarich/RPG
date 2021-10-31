#include"../header/PeopleMap.h"
#include"../header/Function.h"
#include"../header/PeopleInfoList.h"
#include"../header/MapInfoList.h"
#include"../header/EventInfoList.h"
#include"../header/ObjectMap.h"
#include"../header/BossMap.h"

GHandle PeopleMap::graph[Define::PEOPLE_KIND_MAX][(int)Direction::SIZE * 3];

PeopleMap::PeopleMap(int peopleKind, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, Vector2<double>& camera, int& mapNum) :peopleKind(peopleKind), playerMap(playerMap), enemyMapList(enemyMapList), camera(camera), mapNum(mapNum), bossMapList(bossMapList), objectMapList(objectMapList)
{
	masuPosition = Vector2<int>(PeopleInfoList::GetPeopleInfoList()[peopleKind].x, PeopleInfoList::GetPeopleInfoList()[peopleKind].y);
	defaultMasuPosition = masuPosition;
	position = Vector2<double>(masuPosition.x*Define::MASU_SIZE + (double)Define::MASU_SIZE / 2, masuPosition.y*Define::MASU_SIZE + (double)Define::MASU_SIZE / 2);
	direction = PeopleInfoList::GetPeopleInfoList()[peopleKind].defaultDirection;
	moveState = MoveState::STOP;

	velocity = Vector2<double>(0.0, 0.0);
	moveTime = 0;
	moveEndTime = 0;
	moveIntervalTimer = 0;
}

PeopleMap::~PeopleMap()
{

}

void PeopleMap::Load()
{
	for (int i = 0; i < Define::PEOPLE_KIND_MAX; i++)
	{
		stringstream ss;
		ss << "data/graph/character/people/people" << Function::NumToStringFillZero(i, 2) << ".png";
		int result = LoadDivGraph(ss.str().c_str(), 12, 3, (int)Direction::SIZE, 32, 32, graph[i]);

		assert(result == 0 && "PeopleMap::Load()‚É‚Ä‰æ‘œ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
	}
}

void PeopleMap::Update()
{
	UpdateMove();
}

void PeopleMap::UpdateMove()
{
	if (!PeopleInfoList::GetPeopleInfoList()[peopleKind].canMove)
	{
		return;
	}
	UpdateMoveIntervalTimer();

	if (moveIntervalTimer >= Define::PEOPLE_MOVE_INTERVAL)
	{
		StartMove();
		Move();
	}
}

void PeopleMap::UpdateMoveIntervalTimer()
{
	if (moveState == MoveState::STOP)
	{
		moveIntervalTimer++;
	}
}

void PeopleMap::StartMove()
{
	if (moveState != MoveState::STOP)
	{
		return;
	}

	Direction moveDirection = (Direction)(GetRand(100) % 4);

	bool canMoveToNextPosition = false;
	switch (moveDirection)
	{
	case Direction::DOWN:
	{
		Vector2<int> nextPosition = masuPosition + Vector2<int>(0, 1);
		if ((abs(nextPosition.x - defaultMasuPosition.x) + abs(nextPosition.y - defaultMasuPosition.y)) <= Define::PEOPLE_MOVE_DISTANCE_FROM_DEFAULT_POSITION)
		{
			if (CanMoveToNextPosition(nextPosition,Direction::DOWN))
			{
				canMoveToNextPosition = true;
				velocity = Vector2<double>::DOWN*Define::PEOPLE_MOVE_SPEED;
				masuPosition.y++;
				direction = Direction::DOWN;
			}
		}
	}
	break;
	case Direction::LEFT:
	{
		Vector2<int> nextPosition = masuPosition + Vector2<int>(-1, 0);
		if ((abs(nextPosition.x - defaultMasuPosition.x) + abs(nextPosition.y - defaultMasuPosition.y)) <= Define::PEOPLE_MOVE_DISTANCE_FROM_DEFAULT_POSITION)
		{
			if (CanMoveToNextPosition(nextPosition,Direction::LEFT))
			{
				canMoveToNextPosition = true;
				velocity = Vector2<double>::LEFT*Define::PEOPLE_MOVE_SPEED;
				masuPosition.x--;
				direction = Direction::LEFT;
			}
		}
	}
	break;
	case Direction::RIGHT:
	{
		Vector2<int> nextPosition = masuPosition + Vector2<int>(1, 0);
		if ((abs(nextPosition.x - defaultMasuPosition.x) + abs(nextPosition.y - defaultMasuPosition.y)) <= Define::PEOPLE_MOVE_DISTANCE_FROM_DEFAULT_POSITION)
		{
			if (CanMoveToNextPosition(nextPosition,Direction::RIGHT))
			{
				canMoveToNextPosition = true;
				velocity = Vector2<double>::RIGHT*Define::PEOPLE_MOVE_SPEED;
				masuPosition.x++;
				direction = Direction::RIGHT;
			}
		}
	}
	break;
	case Direction::UP:
	{
		Vector2<int> nextPosition = masuPosition + Vector2<int>(0, -1);
		if ((abs(nextPosition.x - defaultMasuPosition.x) + abs(nextPosition.y - defaultMasuPosition.y)) <= Define::PEOPLE_MOVE_DISTANCE_FROM_DEFAULT_POSITION)
		{
			if (CanMoveToNextPosition(nextPosition,Direction::UP))
			{
				canMoveToNextPosition = true;
				velocity = Vector2<double>::UP*Define::PEOPLE_MOVE_SPEED;
				masuPosition.y--;
				direction = Direction::UP;
			}
		}
	}
	break;
	}

	if (!canMoveToNextPosition)
	{
		return;
	}

	moveEndTime = (int)((double)Define::MASU_SIZE / Define::PEOPLE_MOVE_SPEED);
	moveState = MoveState::WALK;
}

bool PeopleMap::CanMoveToNextPosition(Vector2<int> nextPosition,Direction nextDirection)
{
	bool flag = true;
	
	if (!MapInfoList::GetMapInfoList()[mapNum].canThrough[nextPosition.y][nextPosition.x])
	{
		return false;
	}

	if (MapInfoList::GetMapInfoList()[mapNum].event[nextPosition.y][nextPosition.x] != -1)
	{
		if (!EventInfoList::GetEventInfoList()[MapInfoList::GetMapInfoList()[mapNum].event[nextPosition.y][nextPosition.x]].canThrough)
		{
			return false;
		}
	}

	if (find_if(bossMapList.begin(), bossMapList.end(), [&](BossMapPtr& obj) {return count_if(obj->GetMasuPosition().begin(), obj->GetMasuPosition().end(), [&](const Vector2<int>& pos) {return pos == nextPosition; }) > 0; }) != bossMapList.end())
	{
		return false;
	}

	for (auto& obj : objectMapList)
	{
		if (!obj->GetCanThrough() && obj->GetMasuPosition() == nextPosition)
		{
			return false;
		}
	}

	if (nextPosition == playerMap->GetMasuPosition())
	{
		return false;
	}

	if (find_if(enemyMapList.begin(), enemyMapList.end(), [&](EnemyMapPtr& obj) {return obj->GetMasuPosition() == nextPosition; }) != enemyMapList.end())
	{
		return false;
	}

	switch (nextDirection)
	{
	case Direction::UP:
		for (auto n : MapInfoList::GetCannotThroughUp())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughUpObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughDown())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y - 1][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughDownObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y - 1][masuPosition.x] == n)
			{
				return false;
			}
		}
		break;
	case Direction::DOWN:
		for (auto n : MapInfoList::GetCannotThroughDown())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughDownObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughUp())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y + 1][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughUpObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y + 1][masuPosition.x] == n)
			{
				return false;
			}
		}
		break;
	case Direction::RIGHT:
		for (auto n : MapInfoList::GetCannotThroughRight())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughRightObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughLeft())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x + 1] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughLeftObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x + 1] == n)
			{
				return false;
			}
		}
		break;
	case Direction::LEFT:
		for (auto n : MapInfoList::GetCannotThroughLeft())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughLeftObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughRight())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapChip[masuPosition.y][masuPosition.x - 1] == n)
			{
				return false;
			}
		}
		for (auto n : MapInfoList::GetCannotThroughRightObject())
		{
			if (MapInfoList::GetMapInfoList()[mapNum].mapObject[0][masuPosition.y][masuPosition.x - 1] == n)
			{
				return false;
			}
		}
		break;
	}

	return true;
}

void PeopleMap::Move()
{
	if (moveState == MoveState::STOP)
	{
		return;
	}
	
	position += velocity;

	moveTime++;
	if (moveTime == moveEndTime)
	{
		moveTime = 0;
		moveIntervalTimer = 0;
		moveState = MoveState::STOP;
		position = Vector2<double>((double)masuPosition.x, (double)masuPosition.y)*(double)Define::MASU_SIZE + Vector2<double>((double)Define::MASU_SIZE / 2, (double)Define::MASU_SIZE / 2);
	}
}


void PeopleMap::Draw()
{
	int animationFrame;
	if (moveState == MoveState::WALK)
	{
		animationFrame = ((moveTime + 10) / 5) % 3;
	}
	else
	{
		animationFrame = 1;
	}

	DrawRotaGraphF((float)(position.x-camera.x), (float)(position.y-camera.y), 1.0, 0.0, graph[PeopleInfoList::GetPeopleInfoList()[peopleKind].graphNum][(int)direction * 3 + animationFrame], TRUE);
}

void PeopleMap::Turn(Direction playerDirection)
{
	if (PeopleInfoList::GetPeopleInfoList()[peopleKind].canTurn)
	{
		switch (playerDirection)
		{
		case Direction::DOWN:
			direction = Direction::UP;
			break;
		case Direction::LEFT:
			direction = Direction::RIGHT;
			break;
		case Direction::RIGHT:
			direction = Direction::LEFT;
			break;
		case Direction::UP:
			direction = Direction::DOWN;
			break;
		}
	}
}

void PeopleMap::Talked()
{
	if (PeopleInfoList::GetPeopleInfoList()[peopleKind].nextNum != -1)
	{
		peopleKind = PeopleInfoList::GetPeopleInfoList()[peopleKind].nextNum;
	}
}
