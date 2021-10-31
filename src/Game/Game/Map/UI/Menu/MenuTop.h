#pragma once

#include"Define.h"
#include"PlayerData.h"

class MenuTop
{
public:
	enum struct Topic
	{
		ITEM,
		SKILL,
		EQUIP,
		SYNTHESIS,
		ACHIEVEMENT,
		SAVE,
		TITLE,
		SIZE
	};
private:
	static GHandle conditionErrorGraph[(int)ConditionError::SIZE];
private:
	PlayerData* playerData;
	bool closeFlag;
	bool pushFlag;
	Topic topic;
	bool canSave;
private:
	void MoveCursor();
	void Push();
	void DrawCharacterStatus();
	void DrawHoldMoney();
	void DrawPlayTime();
public:
	MenuTop(PlayerData* playerData, bool canSave);
	~MenuTop();
	static void Load();
	void Update();
	void Draw();
	void Reset();

	bool GetCloseFlag()const { return closeFlag; }
	bool GetPushFlag()const { return pushFlag; }
	Topic GetTopic()const { return topic; }
};