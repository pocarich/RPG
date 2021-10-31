#pragma once

#include"Define.h"
#include"CharacterSkillInfo.h"

class CharacterSkillInfoList
{
private:
	static vector<CharacterSkillInfo> characterSkillInfoList;

public:
	static void Load();
	static const vector<CharacterSkillInfo>& GetCharacterSkillInfoList() { return characterSkillInfoList; }
};