#include"../header/MapInfo.h"

void MapInfo::Reset()
{
	for (int i = 0; i < heightNum; i++)for (int j = 0; j < widthNum; j++)
	{
		areaChange[i][j] = -1;
		event[i][j] = -1;
	}
}