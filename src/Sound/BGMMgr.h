
/*   BGMä«óù   */

#pragma once

#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"

class BGMMgr :public Singleton
{
	static MHandle BGM[7];
	static bool BGMStartFlag[7];
	static bool BGMStopFlag[7];
public:
	static void Load();
	static void Play();
	static void UpdateStartFlag(int);
	static void UpdateStopFlag(int);
};
