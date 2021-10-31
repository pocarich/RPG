#pragma once

#include"Define.h"
#include"BossSpawnInfo.h"

class BossSpawnInfoList
{
private:
	static vector<BossSpawnInfo> bossSpawnInfoList;

public:
	static void Load();
	static const vector<BossSpawnInfo>& GetBossSpawnInfoList() { return bossSpawnInfoList; }
};