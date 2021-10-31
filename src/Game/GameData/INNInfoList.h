#pragma once

#include"INNInfo.h"

class INNInfoList
{
	static vector<INNInfo> _INNInfoList;
public:
	static void Load();
	static const vector<INNInfo>& GetINNInfoList() { return _INNInfoList; }
};