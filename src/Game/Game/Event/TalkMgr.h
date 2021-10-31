#pragma once

#include"Define.h"

class TalkMgr
{
private:
	int peopleKind;
	list<WindowPtr>& windowList;
	bool endFlag;
	int state;
public:
	TalkMgr(int peopleKind, list<WindowPtr>& windowList);
	void Update();
	bool GetEndFlag()const { return endFlag; }
};