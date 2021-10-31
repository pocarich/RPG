#pragma once

#include"PeopleInfo.h"

class PeopleInfoList
{
private:
	static vector<PeopleInfo> peopleInfoList;
public:
	static void Load();
	static const vector<PeopleInfo>& GetPeopleInfoList() { return peopleInfoList; }
};