#include"../header/MapChangeInfoList.h"
#include"../header/Function.h"

vector<MapChangeInfo> MapChangeInfoList::mapChangeInfoList;

void MapChangeInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/map/data/mapChange.csv");

	assert(!ifs.fail() && "MapChangeInfoList::Load()");

	string readString;

	getline(ifs, readString);

	while (getline(ifs, readString))
	{
		MapChangeInfo mapChangeInfo;

		auto element = Function::split(readString, ',');
		assert(element.size() == 10 && "MapChangeInfoList::Load() サイズが不正です。");

		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			int num;
			ss << element[i];
			switch (i)
			{
			case 0:
				ss >> mapChangeInfo.mapNum;
				break;
			case 1:
				ss >> mapChangeInfo.x;
				break;
			case 2:
				ss >> mapChangeInfo.y;
				break;
			case 3:
				ss >> num;
				mapChangeInfo.direction = (Direction)num;
				break;
			case 4:
				ss >> mapChangeInfo.nextMapNum;
				break;
			case 5:
				ss >> mapChangeInfo.nextX;
				break;
			case 6:
				ss >> mapChangeInfo.nextY;
				break;
			case 7:
				ss >> num;
				mapChangeInfo.nextDirection = (Direction)num;
				break;
			case 8:
				ss >> mapChangeInfo.appearFlag;
				break;
			case 9:
				ss >> mapChangeInfo.disappearFlag;
				break;
			}
		}
		mapChangeInfoList.push_back(mapChangeInfo);
	}

	ifs.close();
}