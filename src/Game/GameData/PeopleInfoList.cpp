#include"../header/PeopleInfoList.h"
#include"../header/Function.h"

vector<PeopleInfo> PeopleInfoList::peopleInfoList;

void PeopleInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/map/people/PeopleInfoList.csv");

	assert(!ifs.fail() && "PeopleInfoList::Load()");

	string readString;

	getline(ifs, readString);

	while (getline(ifs, readString))
	{
		PeopleInfo peopleInfo;

		auto element = Function::split(readString, ',');
		assert(element.size() == 16 && "PeopleInfoList::Load() サイズが不正です。");

		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			int num;
			ss << element[i];
			switch (i)
			{
			case 0:
				ss >> peopleInfo.name;
			case 1:
				ss >> peopleInfo.mapNum;
				break;
			case 2:
				ss >> peopleInfo.x;
				break;
			case 3:
				ss >> peopleInfo.y;
				break;
			case 4:
				ss >> num;
				peopleInfo.defaultDirection = (Direction)num;
				break;
			case 5:
				ss >> peopleInfo.graphNum;
				break;
			case 6:
				ss >> num; 
				peopleInfo.canMove = num == 1;
				break;
			case 7:
				ss >> num; 
				peopleInfo.canTurn = num == 1;
				break;
			case 8:
				ss >> peopleInfo.appearFlag;
				break;
			case 9:
				ss >> peopleInfo.disappearFlag;
				break;
			case 10:
				ss >> peopleInfo.nextNum;
				break;
			case 11:
				ss >> peopleInfo.standFlag;
				break;
			case 12:
				ss >> peopleInfo.specialEvent;
				break;
			case 13:
			{
				auto element2 = Function::split(ss.str(), '|');
				for (int j = 0; j != element2.size(); j++)
				{
					stringstream ss1;
					int num;
					ss1 << element2[j];
					ss1 >> num;
					if (num != -1)
					{
						peopleInfo.getItems.push_back(num);
					}
				}
			}
			break;
			case 14:
			{
				auto element2 = Function::split(ss.str(), '|');
				for (int j = 0; j != element2.size(); j++)
				{
					stringstream ss1;
					int num;
					ss1 << element2[j];
					ss1 >> num;
					if (num != -1)
					{
						peopleInfo.giveItems.push_back(num);
					}
				}
			}
			break;
			case 15:
				peopleInfo.message = Function::split(element[i], '|');
				break;
			}
		}
		peopleInfoList.push_back(peopleInfo);
	}

	ifs.close();
}