#include"../header/INNInfoList.h"
#include"../header/Function.h"

vector<INNInfo> INNInfoList::_INNInfoList;

void INNInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/data/INN/INNInfoList.csv");

	assert(!ifs.fail() && "INNInfoList::Load()");

	string readString;

	getline(ifs, readString);

	while (getline(ifs, readString))
	{
		INNInfo _INNInfo;

		auto element = Function::split(readString, ',');
		assert(element.size() == 3 && "INNInfoList::Load() サイズが不正です。");

		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			int num;
			ss << element[i];
			switch (i)
			{
			case 0:
				ss >> _INNInfo.name;
				break;
			case 1:
				ss >> _INNInfo.payMoney;
				break;
			case 2:
			{
				auto element2 = Function::split(ss.str(), '|');
				assert(element2.size() == 4 && "INNInfoList::Load() サイズが不正です。");

				for (int j = 0; j != element2.size(); j++)
				{
					_INNInfo.messages.push_back(element2[j]);
				}
			}
			break;
			}
		}
		_INNInfoList.push_back(_INNInfo);
	}

	ifs.close();
}