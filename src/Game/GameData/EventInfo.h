#pragma once

#include"Define.h"

class EventInfo
{
public:
	enum struct EventType
	{
		CHECK,
		ON
	};
public:
	int mapNum;
	int x;
	int y;
	EventType type;
	bool canThrough;
	int graphKind;
	vector<int> getItems;
	vector<int> giveItems;
	int specialEventNum;
	int appearFlag;
	int disappearFlag;
	int nextNum;
	int standFlag;
	vector<int> direction;
	vector<string> messages;
};