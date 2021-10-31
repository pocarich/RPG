#include"../header/ShopInfoList.h"
#include"../header/Function.h"

vector<ShopInfo> ShopInfoList::shopInfoList;

void ShopInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/data/shop/ShopInfoList.csv");

	assert(!ifs.fail() && "ShopInfoList::Load()");

	string readString;

	getline(ifs, readString);

	while (getline(ifs, readString)) 
	{
		ShopInfo shopInfo;

		auto element = Function::split(readString, ',');
		assert(element.size() == 3 && "ShopInfoList::Load() サイズが不正です。");

		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			int num;
			ss << element[i];
			switch (i)
			{
			case 0:
				ss >> shopInfo.name;
				break;
			case 1:
			{
				auto element2 = Function::split(ss.str(), '|');
				assert(element2.size() == 2 && "ShopInfoList::Load() サイズが不正です。");

				shopInfo.message[0] = element2[0];
				shopInfo.message[1] = element2[1];
			}
				break;
			case 2:
			{
				auto element2 = Function::split(ss.str(), '|');
				for (int l = 0; l != element2.size(); l++)
				{
					stringstream ss2;
					int num;
					ss2 << element2[l];
					ss2 >> num;
					shopInfo.itemList.push_back(num);
				}
			}
				break;
			}
		}
		shopInfoList.push_back(shopInfo);
	}

	ifs.close();
}