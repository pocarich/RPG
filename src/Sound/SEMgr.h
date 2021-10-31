
/*   SEä«óù   */

#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"

class SEMgr :public Singleton
{
	static MHandle SEList[21];
	static bool SEFlag[21];
public:
	static void Load();
	static void Play();
	static void UpdateFlag(int);
};