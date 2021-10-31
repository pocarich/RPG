#pragma once

#include"Define.h"
#include"SpecialEventInfo.h"

class SpecialEventInfoList
{
	static vector<SpecialEventInfo> specialEventInfoList;
public:
	static void Load();
	static const vector<SpecialEventInfo>& GetSpecialEventInfoList() { return specialEventInfoList; }
};