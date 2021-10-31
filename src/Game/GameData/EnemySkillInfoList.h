#pragma once

#include"Define.h"
#include"EnemySkillInfo.h"

class EnemySkillInfoList
{
private:
	static vector<EnemySkillInfo> enemySkillInfoList;
public:
	static void Load();
	static const vector<EnemySkillInfo>& GetEnemySkillInfoList() { return enemySkillInfoList; }
};