#pragma once

#include"Define.h"

class EventMgr
{
private:
	int eventKind;
	list<WindowPtr>& windowList;
	bool endFlag;
	int state;
public:
	EventMgr(int eventKind, list<WindowPtr>& windowList);
	void Update();
	bool GetEndFlag()const { return endFlag; }
};