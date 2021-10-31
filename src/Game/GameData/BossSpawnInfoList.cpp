#include"../header/BossSpawnInfoList.h"
#include"../header/Function.h"

vector<BossSpawnInfo> BossSpawnInfoList::bossSpawnInfoList;

void BossSpawnInfoList::Load()
{
	ifstream ifs;

	ifs.open("data/csv/map/monster/BossSpawnInfo.csv");

	assert(!ifs.fail() && "BossSpawnInfoList::Load()");

	string readString;

	while (true)
	{
		BossSpawnInfo bossSpawnInfo;

		getline(ifs, readString);
		if (readString == "")
		{
			break;
		}
		auto element = Function::split(readString, ',');
		assert(element.size() == 9 && "BossSpawnInfoList::Load() サイズが不正です。");

		for (int k = 0; k != element.size(); k++)
		{
			stringstream ss;
			int num;
			ss << element[k];
			switch (k)
			{
			case 0:
				ss >> bossSpawnInfo.mapNum;
				break;
			case 1:
			{
				auto element2 = Function::split(ss.str(), '|');
				assert(element2.size() == 2 && "BossSpawnInfoList::Load() サイズが不正です。");
				for (int j = 0; j != element2.size(); j++)
				{
					int num;
					stringstream ss1;
					ss1 << element2[j];
					ss1 >> num;
					switch (j)
					{
					case 0:
						bossSpawnInfo.popPlayerPosition.x = num;
						break;
					case 1:
						bossSpawnInfo.popPlayerPosition.y = num;
						break;
					}
				}
			}
				break;
			case 2:
			{
				auto element2 = Function::split(ss.str(), '|');
				assert(element2.size() == 2 && "BossSpawnInfoList::Load() サイズが不正です。");
				for (int j = 0; j != element2.size(); j++)
				{
					int num;
					stringstream ss1;
					ss1 << element2[j];
					ss1 >> num;
					switch (j)
					{
					case 0:
						bossSpawnInfo.popBossPosition.x = num;
						break;
					case 1:
						bossSpawnInfo.popBossPosition.y = num;
						break;
					}
				}
			}
			break;
			case 3:
				ss >> bossSpawnInfo.bossKind;
			break;
			case 4:
				ss >> bossSpawnInfo.popFlag;
				break;
			case 5:
				ss >> bossSpawnInfo.noPopFlag;
				break;
			case 6:
				ss >> bossSpawnInfo.standFlag;
				break;
			case 7:
				ss >> bossSpawnInfo.specialEventNum;
				break;
			case 8:
			{
				auto element2 = Function::split(ss.str(), '&');
				if (element2[0] != "#")
				{
					for (int j = 0; j != element2.size(); j++)
					{
						int kind;
						Vector2<int> tempPos;
						auto element3 = Function::split(element2[j], '|');
						assert(element3.size() == 3 && "BossSpawnInfoList::Load() サイズが不正です。");
						for (int k = 0; k != element3.size(); k++)
						{
							int num;
							stringstream ss1;
							ss1 << element3[k];
							ss1 >> num;
							switch (k)
							{
							case 0:
								kind = num;
								break;
							case 1:
								tempPos.x = num;
								break;
							case 2:
								tempPos.y = num;
								break;
							}
						}
						bossSpawnInfo.popObjectKind.push_back(kind);
						bossSpawnInfo.popObjectPosition.push_back(tempPos);
					}
				}
			}
				break;
			}
		}

		bossSpawnInfoList.push_back(bossSpawnInfo);
	}

	ifs.close();
}