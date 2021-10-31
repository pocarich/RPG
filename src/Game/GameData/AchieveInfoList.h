#pragma once

#include"AchieveInfo.h"

class AchieveInfoList
{
	static vector<AchieveInfo> achieveInfoList;
public:
	static void Load();
	static const vector<AchieveInfo>& GetAchieveInfoList() { return achieveInfoList; }
};