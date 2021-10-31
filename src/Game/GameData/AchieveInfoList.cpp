#include"../header/AchieveInfoList.h"
#include"../header/Function.h"

vector<AchieveInfo> AchieveInfoList::achieveInfoList;

void AchieveInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/data/achievement/AchievementInfoList.csv");

	assert(!ifs.fail() && "AchieveInfoList::Load()");

	string readString;

	getline(ifs, readString);

	while (getline(ifs, readString))
	{
		AchieveInfo achieveInfo;

		auto element = Function::split(readString, ',');
		assert(element.size() == 2 && "AchieveInfoList::Load() サイズが不正です。");

		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			int num;
			ss << element[i];
			switch (i)
			{
			case 0:
				ss >> achieveInfo.name;
				break;
			case 1:
				ss >> achieveInfo.message;
				break;
			}
		}
		achieveInfoList.push_back(achieveInfo);
	}

	ifs.close();
}