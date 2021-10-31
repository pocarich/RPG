#include"../header/EnemySkillInfoList.h"
#include"../header/Function.h"

vector<EnemySkillInfo> EnemySkillInfoList::enemySkillInfoList;

void EnemySkillInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/enemy/EnemySkill.csv");

	assert(!ifs.fail() && "EnemySkillInfoList::Load()");

	string readString;
	getline(ifs, readString);

	while (true)
	{
		EnemySkillInfo enemySkillInfo;

		getline(ifs, readString);
		if (readString == "")
		{
			break;
		}
		auto element = Function::split(readString, ',');
		assert(element.size() == 6 && "EnemySkillInfoList::Load() サイズが不正です。");

		for (int k = 0; k != element.size(); k++)
		{
			stringstream ss;
			int num;
			ss << element[k];
			switch (k)
			{
			case 0:
				ss >> enemySkillInfo.name;
				break;
			case 1:
				ss >> enemySkillInfo.description;
				break;
			case 2:
			{
				auto element2 = Function::split(ss.str(), '/');
				assert(element2.size() == Define::ENEMY_SKILL_ATTRIBUTE_NUM && "EnemySkillInfoList::Load() サイズが不正です。");
				for (int j = 0; j != element2.size(); j++)
				{
					int num2;
					stringstream ss1;
					ss1 << element2[j];
					ss1 >> num2;
					enemySkillInfo.attribute[j] = num2;
				}
			}
			break;
			case 3:
				ss >> enemySkillInfo.value;
				break;
			case 4:
				ss >> enemySkillInfo.stiff;
				break;
			case 5:
				ss >> enemySkillInfo.delay;
				break;
			}
		}
		enemySkillInfoList.push_back(enemySkillInfo);
	}

	ifs.close();
}