#pragma once

#include"Define.h"
#include"PlayerData.h"

class MenuAchievement
{
private:
	static GHandle cursor;
	static GHandle conditionErrorGraph[(int)ConditionError::SIZE];
private:
	PlayerData* playerData;
	int cursorNum1;
	int offset;
	bool closeFlag;
private:
	void MoveCursor();
	void Push();
	void DrawCharacterStatus();
	void DrawTopic();
public:
	MenuAchievement(PlayerData* playerData);
	~MenuAchievement();
	static void Load();
	void Update();
	void Draw();
	bool GetCloseFlag()const { return closeFlag; }
};