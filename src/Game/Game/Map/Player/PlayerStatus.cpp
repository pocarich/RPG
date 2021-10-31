#include"../header/PlayerStatus.h"
#include"../header/ItemInfoList.h"

PlayerStatus::PlayerStatus(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int loadDataNum)
{
	stopTime = 0;
	money = 1000;
	for (int i = 0; i < Define::ITEM_KIND; i++)
	{
		holdItemList.push_back(0);
	}

	if (loadDataNum != -1)
	{
		this->money = saveDataList[loadDataNum].money;
		for (int i = 0; i < Define::ITEM_KIND; i++)
		{
			this->holdItemList[i] = saveDataList[loadDataNum].holdItemList[i];
		}
	}
}

PlayerStatus::~PlayerStatus()
{

}

void PlayerStatus::AddMoney(int value)
{
	money += value;
}

void PlayerStatus::UseMoney(int value)
{
	money -= value;
	money = max(0, money);
}

void PlayerStatus::SellItem(int itemKindNum)
{
	holdItemList[itemKindNum]--;
	assert(holdItemList[itemKindNum] >= 0 && "PlayerStatus::SellItem()");
	money += ItemInfoList::GetItemInfoList()[itemKindNum].sellMoney;
}

void PlayerStatus::AddItem(int itemKindNum)
{
	holdItemList[itemKindNum]++;
	holdItemList[itemKindNum] = min(holdItemList[itemKindNum], ItemInfoList::GetItemInfoList()[itemKindNum].maxHoldNum);
}

void PlayerStatus::UseItem(int itemKindNum)
{
	holdItemList[itemKindNum]--;
	assert(holdItemList[itemKindNum] >= 0 && "PlayerStatus()::UseItem()");

	auto info = ItemInfoList::GetItemInfoList()[itemKindNum];

	if (info.option[(int)ItemInfo::ItemOption::STOP_TIME] > 0.001)
	{
		stopTime = (int)info.option[(int)ItemInfo::ItemOption::STOP_TIME];
	}
}

void PlayerStatus::Save(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int saveDataNum)
{
	saveDataList[saveDataNum].money = money;
	for (int i = 0; i < Define::ITEM_KIND; i++)
	{
		saveDataList[saveDataNum].holdItemList[i] = holdItemList[i];
	}
}