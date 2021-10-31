#pragma once

#include"Define.h"
#include"PlayerData.h"

class MenuTitle
{
private:
	static GHandle conditionErrorGraph[(int)ConditionError::SIZE];
	static const int DARK_TIME = 120;
private:
	PlayerData* playerData;
	bool closeFlag;
	int cursorNum1;
	bool goTitle;
	bool pushFlag;
	int timer;
	int darkAlpha;
private:
	void MoveCursor();
	void Push();
	void DrawCharacterStatus();
	void DrawTopic();
public:
	MenuTitle(PlayerData* playerData);
	~MenuTitle();
	static void Load();
	void Update();
	void Draw();
	bool GetCloseFlag()const { return closeFlag; }
	bool GetGoTitle()const { return goTitle; }
};