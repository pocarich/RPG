#pragma once

#include"Define.h"
#include"Class.h"

class MapInfo
{
public:
	string name;
	int heightNum, widthNum;
	int mapChip[Define::MAP_HEIGHT_MAX][Define::MAP_WIDTH_MAX];
	int mapObject[2][Define::MAP_HEIGHT_MAX][Define::MAP_WIDTH_MAX];
	bool canThrough[Define::MAP_HEIGHT_MAX][Define::MAP_WIDTH_MAX];
	int areaChange[Define::MAP_HEIGHT_MAX][Define::MAP_WIDTH_MAX];
	int event[Define::MAP_HEIGHT_MAX][Define::MAP_WIDTH_MAX];
	vector<int> monsterKindList;
	vector<Vector2<int>> monsterPopPositionList;
	vector<int> popObjectKindList;
	vector<Vector2<int>> popObjectPositionList;
	vector<int> objectPopFlag;
	vector<int> objectNotPopFlag;
public:
	void Reset();
};