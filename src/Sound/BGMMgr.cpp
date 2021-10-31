#include"../header/BGMMgr.h"
#include"../header/Function.h"

MHandle BGMMgr::BGM[7];
bool BGMMgr::BGMStartFlag[7];
bool BGMMgr::BGMStopFlag[7];

void BGMMgr::Load()
{
	for (int i = 0; i < 7; i++)
	{
		BGMStartFlag[i] = false;
		BGMStopFlag[i] = false;
	}
}

void BGMMgr::Play()
{
	for (int i = 0; i < 7; i++)
	{
		if (BGMStartFlag[i])
		{
			BGMStartFlag[i] = false;
			PlaySoundMem(BGM[i], DX_PLAYTYPE_LOOP);
		}
		if (BGMStopFlag[i])
		{
			BGMStopFlag[i] = false;
			StopSoundMem(BGM[i]);
		}
	}
}

void BGMMgr::UpdateStartFlag(int num)
{
	BGMStartFlag[num] = true;
}

void BGMMgr::UpdateStopFlag(int num)
{
	BGMStopFlag[num] = true;
}