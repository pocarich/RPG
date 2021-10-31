#pragma once

#include"Define.h"
#include"PlayerData.h"

class MenuSkill
{
private:
	static GHandle keyGraph[3];
	static GHandle downCursor;
	static GHandle cursor;
	static GHandle conditionErrorGraph[(int)ConditionError::SIZE];
private:
	PlayerData* playerData;
	int state;
	int cursorNum1;
	int cursorNum2;
	int cursorNum3;
	int cursorNum4;
	int offset;
	int cursorTimer;
	bool closeFlag;
private:
	void MoveCursor();
	void Push();
	void DrawCharacterStatus();
	void DrawTopic();
	int CanSelect();
	int CanSelect2();
	void UseSkill();
public:
	MenuSkill(PlayerData* playerData);
	~MenuSkill();
	static void Load();
	void Update();
	void Draw();
	bool GetCloseFlag()const { return closeFlag; }
};