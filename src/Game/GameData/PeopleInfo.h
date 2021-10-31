#pragma once

#include"Define.h"

class PeopleInfo
{
public:
	string name;
	int mapNum;
	int x;
	int y;
	Direction defaultDirection;
	int graphNum;
	bool canMove;
	bool canTurn;
	int appearFlag;
	int disappearFlag;
	int nextNum;
	int standFlag;
	int specialEvent;
	vector<int> getItems;
	vector<int> giveItems;
	vector<string> message;
};