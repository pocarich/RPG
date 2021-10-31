#pragma once

#include"Define.h"
#include"PlayerData.h"
#include"Window.h"

class Shop
{
private:
	static GHandle cursor;
private:
	PlayerData* playerData;
	list<WindowPtr> windowList;
	vector<pair<int, int>> tempItemList;
	int shopNum;
	int cursorNum1;
	int cursorNum2;
	int cursorNum3;
	int cursorNum4;
	int offset;
	bool closeFlag;
	int state;
private:
	void UpdateTempItemList();
	void MoveCursor();
	void Push();
	void BuyItem();
	void SellItem();
public:
	Shop(PlayerData* playerData, int shopNum);
	~Shop();
	static void Load();
	void Update();
	void Draw();
	bool GetCloseFlag()const { return closeFlag; }
};