#pragma once

#include"Define.h"
#include"PlayerData.h"

class MenuEquip
{
private:
	static GHandle downCursor;
	static GHandle cursor;
	static GHandle conditionErrorGraph[(int)ConditionError::SIZE];
private:
	PlayerData* playerData;
	bool closeFlag;
	vector<int> tempItemList;
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
	void SetEquip();
	void RemoveEquip();
public:
	MenuEquip(PlayerData* playerData);
	~MenuEquip();
	static void Load();
	void Update();
	void Draw();
	bool GetCloseFlag()const { return closeFlag; }
};