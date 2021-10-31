#include"../header/EventInfoList.h"
#include"../header/Function.h"

vector<EventInfo> EventInfoList::eventInfoList;

void EventInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/map/event/EventInfoList.csv");

	assert(!ifs.fail() && "EventInfoList::Load()");

	string readString;

	getline(ifs, readString);

	while (getline(ifs, readString))
	{
		EventInfo eventInfo;

		auto element = Function::split(readString, ',');
		assert(element.size() == 15 && "EventInfoList::Load() サイズが不正です。");

		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			int num;
			ss << element[i];
			switch (i)
			{
			case 0:
				ss >> eventInfo.mapNum;
				break;
			case 1:
				ss >> eventInfo.x;
				break;
			case 2:
				ss >> eventInfo.y;
				break;
			case 3:
				ss >> num;
				eventInfo.type = (EventInfo::EventType)num;
			case 4:
				ss >> num;
				eventInfo.canThrough = num == 1;
				break;
			case 5:
				ss >> eventInfo.graphKind;
				break;
			case 6:
			{
				auto element2 = Function::split(ss.str(), '|');
				for (int l = 0; l != element2.size(); l++)
				{
					stringstream ss2;
					int num;
					ss2 << element2[l];
					ss2 >> num;
					if (num == -1)
					{
						break;
					}
					eventInfo.getItems.push_back(num);
				}
			}
				break;
			case 7:
			{
				auto element2 = Function::split(ss.str(), '|');
				for (int l = 0; l != element2.size(); l++)
				{
					stringstream ss2;
					int num;
					ss2 << element2[l];
					ss2 >> num;
					if (num == -1)
					{
						break;
					}
					eventInfo.giveItems.push_back(num);
				}
			}
			break;
			case 8:
				ss >> eventInfo.specialEventNum;
				break;
			case 9:
				ss >> eventInfo.appearFlag;
				break;
			case 10:
				ss >> eventInfo.disappearFlag;
				break;
			case 11:
				ss >> eventInfo.nextNum;
				break;
			case 12:
				ss >> eventInfo.standFlag;
				break;
			case 13:
			{
				auto element2 = Function::split(ss.str(), '|');
				for (int l = 0; l != element2.size(); l++)
				{
					stringstream ss2;
					int num;
					ss2 << element2[l];
					ss2 >> num;
					if (num == -1)
					{
						break;
					}
					eventInfo.direction.push_back(num);
				}
			}
				break;
			case 14:
				eventInfo.messages = Function::split(element[i], '|');
				break;
			}
		}
		eventInfoList.push_back(eventInfo);
	}

	ifs.close();
}