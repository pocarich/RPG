#pragma once

#include"Define.h"

class MapChangeInfo
{
public:
	int mapNum;
	int nextMapNum;
	int x;
	int nextX;
	int y;
	int nextY;
	Direction direction;
	Direction nextDirection;
	int appearFlag;
	int disappearFlag;
};