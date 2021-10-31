#pragma once

#include"Define.h"
#include"PlayerMap.h"
#include"Class.h"
#include"EnemyMap.h"

class PeopleMap
{
private:
	static GHandle graph[Define::PEOPLE_KIND_MAX][(int)Direction::SIZE * 3];
private:
	int peopleKind;
	PlayerMap* playerMap;
	list<EnemyMapPtr>& enemyMapList;
	list<BossMapPtr>& bossMapList;
	list<ObjectMapPtr>& objectMapList;
	Vector2<int> masuPosition;
	Vector2<int> defaultMasuPosition;
	Vector2<double> position;
	Direction direction;
	MoveState moveState;
	int& mapNum;

	int moveIntervalTimer;
	Vector2<double> velocity;
	int moveTime;
	int moveEndTime;

	Vector2<double>& camera;
private:
	void UpdateMove();
	void UpdateMoveIntervalTimer();
	void StartMove();
	void Move();
	bool CanMoveToNextPosition(Vector2<int> nextPosition,Direction nextDirection);
public:
	PeopleMap(int peopleKind, PlayerMap* playerMap , list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, Vector2<double>& camera, int& mapNum);
	~PeopleMap();
	static void Load();
	void Update();
	void Draw();
	void Turn(Direction playerDirection);
	void Talked();
	Vector2<int> GetMasuPosition()const { return masuPosition; }
	Vector2<double> GetPosition()const { return position; }
	int GetPeopleKind()const { return peopleKind; }
};