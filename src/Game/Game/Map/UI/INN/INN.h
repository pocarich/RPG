#pragma once

#include"Define.h"
#include"Window.h"
#include"PlayerData.h"

class INN
{
private:
	list<WindowPtr> windowList;
	PlayerData* playerData;
	int state;
	int INNKind;
	bool closeFlag;
	int darkAlpha;
	int INNTimer;
private:
	void UpdateINN();
public:
	INN(PlayerData* playerData, int INNKind);
	void Update();
	void Draw();
	bool GetCloseFlag()const { return closeFlag; }
};