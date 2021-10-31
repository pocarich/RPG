#pragma once

#include"Define.h"
#include"PlayerData.h"

class MenuSynthesis
{
private:
	static GHandle conditionErrorGraph[(int)ConditionError::SIZE];
	static GHandle cursor;
private:
	PlayerData* playerData;
	vector<int> tempItemList;
	int state;
	int cursorNum1;
	int cursorNum2;
	int offset;
	bool closeFlag;
private:
	void UpdateTempItemList();
	void MoveCursor();
	void Push();
	void Synthesis();
	void DrawCharacterStatus();
	void DrawTopic(); 
	int CanSelect();
public:
	MenuSynthesis(PlayerData* playerData);
	~MenuSynthesis();
	static void Load();
	void Update();
	void Draw();
	bool GetCloseFlag()const { return closeFlag; }
};