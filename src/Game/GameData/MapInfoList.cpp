#include"../header/MapInfoList.h"
#include"../header/Function.h"

vector<MapInfo> MapInfoList::mapInfoList;
vector<int> MapInfoList::cannotThroughUp;
vector<int> MapInfoList::cannotThroughRight;
vector<int> MapInfoList::cannotThroughLeft;
vector<int> MapInfoList::cannotThroughDown;
vector<int> MapInfoList::cannotThroughUpObject;
vector<int> MapInfoList::cannotThroughRightObject;
vector<int> MapInfoList::cannotThroughLeftObject;
vector<int> MapInfoList::cannotThroughDownObject;

void MapInfoList::Load()
{
	mapInfoList.clear();

	ifstream ifs;
	int mapNum = 0;
	string readString;
	while (1)
	{
		stringstream mapCSV, monsterCSV, mapInfoCSV;
		MapInfo mapInfo;

		mapCSV << "data/csv/map/chip/map" << Function::NumToStringFillZero(mapNum, 3) << ".csv";
		mapInfoCSV << "data/csv/map/info/mapInfo" << Function::NumToStringFillZero(mapNum, 3) << ".csv";

		ifs.open(mapInfoCSV.str());

		if (ifs.fail())
		{
			break;
		}

		getline(ifs, readString);

		{
			vector<string> element = Function::split(readString, ',');
			assert(count_if(element.begin(), element.end(), [](string& str) {return str != ""; }) == 1 && "MapInfoList::Load() mapChipÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
			stringstream ss_info1, ss_info2;
			ss_info1 << element[0];
			ss_info1 >> mapInfo.name;
		}

		getline(ifs, readString);

		{
			vector<string> element = Function::split(readString, ',');
			assert(count_if(element.begin(), element.end(), [](string& str) {return str != ""; }) == 2 && "MapInfoList::Load() mapChipÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
			stringstream ss_info1, ss_info2;
			ss_info1 << element[0];
			ss_info1 >> mapInfo.widthNum;
			ss_info2 << element[1];
			ss_info2 >> mapInfo.heightNum;
		}

		getline(ifs, readString);

		{
			vector<string> element = Function::split(readString, ',');
			if (element.size()!=0&&element[0] != "")
			{
				for (int i = 0; i != element.size(); i++)
				{
					if (element[i] == "")
					{
						break;
					}
					stringstream ss_info1;
					int num;
					ss_info1 << element[i];
					ss_info1 >> num;
					mapInfo.monsterKindList.push_back(num);
				}
			}
		}

		getline(ifs, readString);

		{
			vector<string> element = Function::split(readString, ',');
			if (element.size() != 0 && element[0] != "")
			{
				for (int i = 0; i != element.size(); i++)
				{
					if (element[i] == "")
					{
						break;
					}
					Vector2<int> pos;
					vector<string> positionElement = Function::split(element[i], '|');
					assert(positionElement.size() == 2 && "MapInfoList::Load() mapChipÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

					stringstream ssx, ssy;
					ssx << positionElement[0];
					ssx >> pos.x;
					ssy << positionElement[1];
					ssy >> pos.y;
					mapInfo.monsterPopPositionList.push_back(pos);
				}
			}
		}

		getline(ifs, readString);

		{
			vector<string> element = Function::split(readString, ',');
			for (int i = 0; i != element.size(); i++)
			{
				if (element[i] == "")
				{
					break;
				}
				int objectKind;
				Vector2<int> popPosition;
				int popFlag;
				int notPopFlag;
				auto element2 = Function::split(element[i], '|');
				assert(element2 .size() == 5 && "MapInfoList::Load() objectPopInfoÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
				for (int j = 0; j != element2.size(); j++)
				{
					stringstream ss;
					ss << element2[j];
					switch (j)
					{
					case 0:
						ss >> objectKind;
						break;
					case 1:
						ss >> popPosition.x;
						break;
					case 2:
						ss >> popPosition.y;
						break;
					case 3:
						ss >> popFlag;
						break;
					case 4:
						ss >> notPopFlag;
						break;
					}
				}
				mapInfo.popObjectKindList.push_back(objectKind);
				mapInfo.popObjectPositionList.push_back(popPosition);
				mapInfo.objectPopFlag.push_back(popFlag);
				mapInfo.objectNotPopFlag.push_back(notPopFlag);
			}
		}

		ifs.close();
		
		ifs.open(mapCSV.str());

		if (ifs.fail())
		{
			break;
		}

		for (int i = 0; i < mapInfo.heightNum; i++)
		{
			getline(ifs, readString);
			vector<string> element = Function::split(readString, ',');
			stringstream ss_mapNum;
			ss_mapNum << mapNum;
			assert(element.size() == mapInfo.widthNum && "MapInfoList::Load() mapChipÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB"&&ss_mapNum.str().c_str());
			for (int j = 0; j != element.size(); j++)
			{
				stringstream ss;
				ss << element[j];
				ss >> mapInfo.mapChip[i][j];
			}
		}

		getline(ifs, readString);

		for (int i = 0; i < mapInfo.heightNum; i++)
		{
			getline(ifs, readString);
			vector<string> element = Function::split(readString, ',');
			assert(element.size() == mapInfo.widthNum &&"MapInfoList::Load() mapObject1ÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
			for (int j = 0; j != element.size(); j++)
			{
				stringstream ss;
				ss << element[j];
				ss >> mapInfo.mapObject[0][i][j];
			}
		}

		getline(ifs, readString);

		for (int i = 0; i < mapInfo.heightNum; i++)
		{
			getline(ifs, readString);
			vector<string> element = Function::split(readString, ',');
			assert(element.size() == mapInfo.widthNum &&"MapInfoList::Load() mapObject2ÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
			for (int j = 0; j != element.size(); j++)
			{
				stringstream ss;
				ss << element[j];
				ss >> mapInfo.mapObject[1][i][j];
			}
		}

		getline(ifs, readString);

		for (int i = 0; i < mapInfo.heightNum; i++)
		{
			getline(ifs, readString);
			vector<string> element = Function::split(readString, ',');
			assert(element.size() == mapInfo.widthNum &&"MapInfoList::Load() canThroughÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
			for (int j = 0; j != element.size(); j++)
			{
				stringstream ss;
				int num;
				ss << element[j];
				ss >> num;
				mapInfo.canThrough[i][j] = num == 1 ? false : true;
			}
		}

		ifs.close();

		mapInfo.Reset();

		mapInfoList.push_back(mapInfo);

		mapNum++;
	}

	ifs.open("data/csv/map/data/CannotThrough.csv");
	assert(!ifs.fail() && "MapInfoList::Load()");

	for (int i = 0; i < 8; i++)
	{
		getline(ifs, readString);
		
		vector<string> element = Function::split(readString, ',');
		if (element[0] == "")
		{
			continue;
		}
		switch (i)
		{
		case 0:
		{
			for (int j = 0; j != element.size(); j++)
			{
				if (element[j] == "")
				{
					continue;
				}
				stringstream ss;
				int num;
				ss << element[j];
				ss >> num;
				cannotThroughUp.push_back(num);
			}
		}
			break;
		case 1:
		{
			for (int j = 0; j != element.size(); j++)
			{
				if (element[j] == "")
				{
					continue;
				}
				stringstream ss;
				int num;
				ss << element[j];
				ss >> num;
				cannotThroughRight.push_back(num);
			}
		}
			break;
		case 2:
		{
			for (int j = 0; j != element.size(); j++)
			{
				if (element[j] == "")
				{
					continue;
				}
				stringstream ss;
				int num;
				ss << element[j];
				ss >> num;
				cannotThroughLeft.push_back(num);
			}
		}
			break;
		case 3:
		{
			for (int j = 0; j != element.size(); j++)
			{
				if (element[j] == "")
				{
					continue;
				}
				stringstream ss;
				int num;
				ss << element[j];
				ss >> num;
				cannotThroughDown.push_back(num);
			}
		}
			break;
		case 4:
		{
			for (int j = 0; j != element.size(); j++)
			{
				if (element[j] == "")
				{
					continue;
				}
				stringstream ss;
				int num;
				ss << element[j];
				ss >> num;
				cannotThroughUpObject.push_back(num);
			}
		}
			break;
		case 5:
		{
			for (int j = 0; j != element.size(); j++)
			{
				if (element[j] == "")
				{
					continue;
				}
				stringstream ss;
				int num;
				ss << element[j];
				ss >> num;
				cannotThroughRightObject.push_back(num);
			}
		}
			break;
		case 6:
		{
			for (int j = 0; j != element.size(); j++)
			{
				if (element[j] == "")
				{
					continue;
				}
				stringstream ss;
				int num;
				ss << element[j];
				ss >> num;
				cannotThroughLeftObject.push_back(num);
			}
		}
			break;
		case 7:
		{
			for (int j = 0; j != element.size(); j++)
			{
				if (element[j] == "")
				{
					continue;
				}
				stringstream ss;
				int num;
				ss << element[j];
				ss >> num;
				cannotThroughDownObject.push_back(num);
			}
		}
			break;
		}
	}

	ifs.close();
}