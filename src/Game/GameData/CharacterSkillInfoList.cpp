#include"../header/CharacterSkillInfoList.h"
#include"../header/Function.h"

vector<CharacterSkillInfo> CharacterSkillInfoList::characterSkillInfoList;

void CharacterSkillInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/character/CharacterSkill.csv");

	assert(!ifs.fail() && "CharacterSkillInfoList::Load()");

	string readString;

	while (true)
	{
		CharacterSkillInfo characterSkillInfo;

		getline(ifs, readString);
		if (readString == "")
		{
			break;
		}
		auto element = Function::split(readString, ',');
		assert(element.size() == 5 && "CharacterSkillInfoList::Load() サイズが不正です。");

		for (int k = 0; k != element.size(); k++)
		{
			stringstream ss;
			int num;
			ss << element[k];
			switch (k)
			{
			case 0:
				ss >> characterSkillInfo.name;
				break;
			case 1:
				ss >> characterSkillInfo.description;
				break;
			case 2:
				ss >> num;
				characterSkillInfo.type = (SkillType)num;
				break;
			case 3:
			{
				auto element2 = Function::split(element[3], '/');
				assert(element2.size() == 4 && "CharacterSkillInfoList::Load() サイズが不正です。");
				for (int j = 0; j != element2.size(); j++)
				{
					int num;
					stringstream ss1;
					ss1 << element2[j];
					ss1 >> num;
					characterSkillInfo.needPoint[j] = num;
				}
			}
				break;
			case 4:
				ss >> characterSkillInfo.defaultLevel;
				break;
			}
		}

		getline(ifs, readString);
		auto elementAttribute = Function::split(readString, ',');
		assert(elementAttribute.size() == Define::ATTRIBUTE_NUM && "CharacterSkillInfoList::Load() サイズが不正です。");

		for (int i = 0; i != elementAttribute.size(); i++)
		{
			int num;
			stringstream ss1;
			ss1 << elementAttribute[i];
			ss1 >> num;
			characterSkillInfo.attribute[i] = num;
		}

		getline(ifs, readString);
		auto elementSP = Function::split(readString, ',');
		assert(elementSP.size() == 5 && "CharacterSkillInfoList::Load() サイズが不正です。");

		for (int i = 0; i != elementSP.size(); i++)
		{
			int num;
			stringstream ss1;
			ss1 << elementSP[i];
			ss1 >> num;
			characterSkillInfo.paySP[i] = num;
		}

		getline(ifs, readString);
		auto elementRate = Function::split(readString, ',');
		assert(elementRate.size() == 5 && "CharacterSkillInfoList::Load() サイズが不正です。");

		for (int i = 0; i != elementRate.size(); i++)
		{
			stringstream ss1;
			ss1 << elementRate[i];
			ss1 >> characterSkillInfo.value[i];
		}

		getline(ifs, readString);
		auto elementStiff = Function::split(readString, ',');
		assert(elementStiff.size() == 5 && "CharacterSkillInfoList::Load() サイズが不正です。");

		for (int i = 0; i != elementStiff.size(); i++)
		{
			int num;
			stringstream ss1;
			ss1 << elementStiff[i];
			ss1 >> num;
			characterSkillInfo.stiff[i] = num;
		}

		characterSkillInfoList.push_back(characterSkillInfo);
	}

	ifs.close();
}