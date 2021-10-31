#pragma once

#include"Define.h"

class EnemySkillInfo
{
public:
	string name;
	string description;
	int attribute[Define::ENEMY_SKILL_ATTRIBUTE_NUM];
	double value;
	int stiff;
	int delay;
};