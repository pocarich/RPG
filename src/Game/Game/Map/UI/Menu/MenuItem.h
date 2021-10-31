#pragma once

#include"Define.h"
#include"PlayerData.h"

class MenuItem
{
private:
	static GHandle downCursor;
	static GHandle cursor;
	static GHandle conditionErrorGraph[(int)ConditionError::SIZE];
private:
	PlayerData* playerData;
	bool closeFlag;
	vector<pair<int, int>> tempItemList;
	int cursorNum1;
	int cursorNum2;
	int cursorNum3;
	int offset;
	int state;
	int cursorTimer;
private:
	void MoveCursor();
	void Push();
	void UpdateTempItemList();
	void DrawCharacterStatus();
	void DrawTopic();
	int CanSelect();
	int CanUse();
	void UseItem();
	void UseItemPlayer();
public:
	MenuItem(PlayerData* playerData);
	~MenuItem();
	static void Load();
	void Update();
	void Draw();
	bool GetCloseFlag()const { return closeFlag; }
};