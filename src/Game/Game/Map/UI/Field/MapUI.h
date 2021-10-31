#pragma once

#include"Define.h"
#include"PlayerMap.h"

class MapUI
{
private:
	enum struct CashKind
	{
		CAN,
		CANNOT,
		UP,
		RIGHT,
		LEFT,
		DOWN,
	};
private:
	PlayerMap* playerMap;
	list<EnemyMapPtr>& enemyMapList;
	list<BossMapPtr>& bossMapList;
	list<ObjectMapPtr>& objectMapList;
	list<PeopleMapPtr>& peopleMapList;
	list<DropItemPtr>& dropItemMapList;
	int& mapNum;
	array<array<vector<CashKind>, Define::MAP_HEIGHT_MAX>, Define::MAP_HEIGHT_MAX> cash;
public:
	MapUI(PlayerMap* playerMap, list<EnemyMapPtr>& enemyMapList, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<PeopleMapPtr>& peopleMapList, list<DropItemPtr>& dropItemMapList,int& mapNum);
	~MapUI();
	void Update();
	void Draw();
	void Cash();
};