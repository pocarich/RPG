#pragma once

#include"Define.h"
#include"Window.h"
#include"MessageWindow.h"

class SpecialEvent
{
protected:
	static GHandle mapBackChip[20 * 30];
	static GHandle mapObjectChip[20 * 20]; 
	static GHandle bossGraph[Define::BOSS_KIND_NUM];
	static GHandle peopleGraph[Define::PEOPLE_KIND_MAX][(int)Direction::SIZE * 3];
	static GHandle playerGraph[Define::CHARACTER_NUM][(int)Direction::SIZE * 3];
protected:
	int eventTimer;
	bool endFlag;
	list<WindowPtr> windowList;
protected:
	virtual void UpdateEvent() = 0;
	void UpdateWindow();
	void UpdateEventTimer();
public:
	SpecialEvent();
	virtual ~SpecialEvent();
	static void Load();
	void Update();
	virtual void Draw() = 0;
	bool GetEndFlag()const { return endFlag; }
};