#pragma once

#include"Define.h"

class CharacterSkillInfo
{
public:
	string name;
	string description;
	SkillType type;
	int attribute[Define::ATTRIBUTE_NUM];
	int needPoint[4];
	int paySP[5];
	double value[5];
	int stiff[5];
	int defaultLevel;
};