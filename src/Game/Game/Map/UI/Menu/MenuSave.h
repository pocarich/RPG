#pragma once

#include"Define.h"
#include"PlayerData.h"

class MenuSave
{
private:
	static GHandle conditionErrorGraph[(int)ConditionError::SIZE];
private:
	PlayerData* playerData;
	bool closeFlag;
	int cursorNum1;
	int cursorNum2;
	int state;
	int saveDataNum;
	array<SaveData, Define::SAVE_DATA_NUM>& saveDataList;
	int& mapNum;
private:
	void MoveCursor();
	void Push();
	void DrawCharacterStatus();
	void DrawTopic();
	void Save();
public:
	MenuSave(PlayerData* playerData, array<SaveData, Define::SAVE_DATA_NUM>& saveDataList,int& mapNum);
	~MenuSave();
	static void Load();
	void Update();
	void Draw();
	void ResetSaveDataNum() { saveDataNum = -1; }
	bool GetCloseFlag()const { return closeFlag; }
	int GetSaveDataNum()const { return saveDataNum; }
};