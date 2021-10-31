
/*   FPSêßå‰   */

#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"

using namespace std;

class FPSMgr
{
	int nowCount;
	int flameCounter;
	array<int, Define::FPS> takeTimes;
	int takeTime;
	double calcedFPS;

	Font FPSFont;
	Color white;
private:
	void Update();
	void Wait();
	void DrawFPS();
	void CalcFPS();
public:
	FPSMgr();
	void Main();
};