#pragma once

#include"Define.h"
#include"Class.h"

class BossSpawnInfo
{
public:
	int mapNum;
	Vector2<int> popPlayerPosition;
	Vector2<int> popBossPosition;
	int bossKind;
	int popFlag;
	int noPopFlag;
	int standFlag;
	int specialEventNum;
	vector<int> popObjectKind;
	vector<Vector2<int>> popObjectPosition;
};