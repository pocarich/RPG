#pragma once

#include"MapChangeInfo.h"

class MapChangeInfoList
{
	static vector<MapChangeInfo> mapChangeInfoList;
public:
	static void Load();
	static const vector<MapChangeInfo>& GetMapChangeInfoList() { return mapChangeInfoList; }
};