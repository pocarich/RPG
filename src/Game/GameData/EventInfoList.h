#pragma once

#include"Define.h"
#include"EventInfo.h"

class EventInfoList
{
	static vector<EventInfo> eventInfoList;
public:
	static void Load();
	static const vector<EventInfo>& GetEventInfoList() { return eventInfoList; }
};