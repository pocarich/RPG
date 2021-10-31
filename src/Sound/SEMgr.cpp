#include"../header/SEMgr.h"
#include"../header/Function.h"

MHandle SEMgr::SEList[21];
bool SEMgr::SEFlag[21];

void SEMgr::Load()
{
	for (int i = 0; i < 21; i++)
	{
		SEFlag[i] = false;
	}
}

void SEMgr::Play()
{
	for (int i = 0; i < 21; i++)
	{
		if (SEFlag[i])
		{
			PlaySoundMem(SEList[i], DX_PLAYTYPE_BACK);
			SEFlag[i] = false;
		}
	}
}

void SEMgr::UpdateFlag(int num)
{
	SEFlag[num] = true;
}