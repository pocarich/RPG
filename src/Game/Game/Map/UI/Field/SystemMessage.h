#pragma once

#include"Define.h"

class SystemMessage
{
	vector<string> messageList;
	vector<int> timer;
public:
	SystemMessage();
	~SystemMessage();
	void Update();
	void Draw();
	void AddMessage(string message);
};