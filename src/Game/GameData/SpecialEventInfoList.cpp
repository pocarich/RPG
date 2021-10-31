#include"../header/SpecialEventInfoList.h"
#include"../header/Function.h"

vector<SpecialEventInfo> SpecialEventInfoList::specialEventInfoList;

void SpecialEventInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/data/event/SpecialEventInfo.csv");

	assert(!ifs.fail() && "SpecialEventInfoList::Load()");

	string readString;

	getline(ifs, readString);
	while (getline(ifs, readString))
	{
		SpecialEventInfo specialEventInfo;

		auto element = Function::split(readString, ',');
		assert(element.size() == 5 && "SpecialEventInfoList::Load() サイズが不正です。");

		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			int num;
			ss << element[i];
			switch (i)
			{
			case 0:
			{
				auto element2 = Function::split(ss.str(), '|');
				for (int j = 0; j != element2.size(); j++)
				{
					stringstream ss2;
					int num;
					ss2 << element2[j];
					ss2 >> num;
					if (num != -1)
					{
						specialEventInfo.getItemList.push_back(num);
					}
				}
			}
			break;
			case 1:
			{
				auto element2 = Function::split(ss.str(), '|');
				for (int j = 0; j != element2.size(); j++)
				{
					stringstream ss2;
					int num;
					ss2 << element2[j];
					ss2 >> num;
					if (num != -1)
					{
						specialEventInfo.giveItemList.push_back(num);
					}
				}
			}
			break;
			case 2:
				ss >> specialEventInfo.standFlag;
				break;
			case 3:
				ss >> specialEventInfo.mapNum;
				break;
			case 4:
			{
				auto element2 = Function::split(ss.str(), '|');
				stringstream ss1, ss2;
				ss1 << element2[0];
				ss2 << element2[1];
				ss1 >> specialEventInfo.masuPosition.x;
				ss2 >> specialEventInfo.masuPosition.y;
			}
				break;
			}
		}
		specialEventInfoList.push_back(specialEventInfo);
	}

	ifs.close();
}