#include"../header/ItemInfoList.h"
#include"../header/Function.h"

vector<ItemInfo> ItemInfoList::itemInfoList;
GHandle ItemInfoList::graph[Define::ITEM_ICON_KIND + 1];

void ItemInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/data/item/itemInfoList.csv");

	assert(!ifs.fail() && "ItemInfoList::Load()");

	string readString;

	getline(ifs, readString);

	while(getline(ifs, readString))
	{
		ItemInfo itemInfo;
		auto element = Function::split(readString, ',');
		assert(element.size() == 14 && "ItemInfoList::Load() サイズが不正です。");

		for (int k = 0; k != element.size(); k++)
		{
			stringstream ss;
			int num;
			ss << element[k];
			switch (k)
			{
			case 0:
				ss >> itemInfo.name;
				break;
			case 1:
				ss >> num;
				itemInfo.type = (ItemInfo::ItemType)num;
				break;
			case 2:
				ss >> itemInfo.graphNum;
				break;
			case 3:
				ss >> itemInfo.description;
				break;
			case 4:
				ss >> itemInfo.HP;
				break;
			case 5:
				ss >> itemInfo.SP;
				break;
			case 6:
				ss >> itemInfo.ATK;
				break;
			case 7:
				ss >> itemInfo.DEF;
				break;
			case 8:
				ss >> itemInfo.INT;
				break;
			case 9:
				ss >> itemInfo.RES;
				break;
			case 10:
			{
				auto element2 = Function::split(ss.str(), '/');
				assert(element2.size() == (int)ItemInfo::ItemOption::SIZE && "CharacterSkillInfoList::Load() サイズが不正です。");
				for (int j = 0; j != element2.size(); j++)
				{
					stringstream ss1;
					ss1 << element2[j];
					ss1 >> itemInfo.option[j];
				}
			}
			break;
			case 11:
				ss >> itemInfo.buyMoney;
				break;
			case 12:
				ss >> itemInfo.sellMoney;
				break;
			case 13:
				ss >> itemInfo.maxHoldNum;
				break;
			}
		}
		itemInfoList.push_back(itemInfo);
	}

	ifs.close();

	for (int i = 1; i <= Define::ITEM_ICON_KIND; i++)
	{
		stringstream ss;
		ss << "data/graph/item/icon/icon" << Function::NumToStringFillZero(i, 3) << ".png";
		graph[i] = LoadGraph(ss.str().c_str());
		assert(graph[i] != 0 && "ItemInfoList::Load()");
	}
}