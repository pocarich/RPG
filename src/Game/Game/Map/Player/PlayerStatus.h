#pragma once

#include"Define.h"
#include"SaveData.h"

class PlayerStatus
{
private:
	int money;
	vector<int> holdItemList;
	int stopTime;
public:
	PlayerStatus(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList,int loadDataNum);
	~PlayerStatus();
	void AddMoney(int value);
	void UseMoney(int value);
	void SellItem(int itemKindNum);
	void AddItem(int itemKindNum);
	void UseItem(int itemKindNum);
	void Save(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int saveDataNum);

	int GetMoney()const { return money; }
	const vector<int>& GetHoldItemList()const { return holdItemList; }
	int GetStopTime()const { return stopTime; }
};