#include"../header/ObjectMap.h"
#include"../header/CharacterSkillInfoList.h"
#include"../header/DamageText.h"
#include"../header/Function.h"
#include"../header/DropItem.h"
#include"../header/ItemInfoList.h"

GHandle ObjectMap::graph[15][30];
vector<int> ObjectMap::graphNumList;
vector<bool> ObjectMap::dispAddFlag;
vector<int> ObjectMap::graphKindList;
vector<bool> ObjectMap::canDestroyList;
vector<bool> ObjectMap::canThroughList;
vector<int> ObjectMap::durabilityList;	//ëœãvíl
vector<int> ObjectMap::hardnessList;
vector<vector<int>> ObjectMap::dropItemList;
vector<vector<int>> ObjectMap::dropRateList;
vector<int> ObjectMap::dispMiniMapList;

ObjectMap::ObjectMap(int kind, Vector2<int> masuPosition, PlayerData* playerData, PlayerMap* playerMap, list<TextUIPtr>& textUIList, list<BattleEffectPtr>& battleEffectList, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<PeopleMapPtr>& peopleMapList, list<EnemyMapPtr>& enemyMapList, list<DropItemPtr>& dropItemMapList, int& mapNum, Vector2<double>& camera) :playerData(playerData), playerMap(playerMap), textUIList(textUIList), battleEffectList(battleEffectList), bossMapList(bossMapList), objectMapList(objectMapList), peopleMapList(peopleMapList), enemyMapList(enemyMapList), dropItemMapList(dropItemMapList), mapNum(mapNum), kind(kind), masuPosition(masuPosition),camera(camera)
{
	animationTimer = 0;
	position = Vector2<double>(masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2, masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2);
	durability = durabilityList[kind];
	deathFlag = false;
}

ObjectMap::~ObjectMap()
{

}

void ObjectMap::Load()
{
	ifstream ifs;
	string str;

	vector<int> widthList;
	vector<int> heightList;
	vector<int> xList;
	vector<int> yList;

	ifs.open("data/csv/object/objectGraph.csv");
	assert(!ifs.fail() && "ObjectMap::Load()Ç…Çƒé∏îsÇµÇ‹ÇµÇΩÅB");

	while (getline(ifs, str))
	{
		int width;
		int height;
		int x;
		int y;

		auto element = Function::split(str, ',');
		assert(element.size() == 5 && "ObjectMap::Load()Çƒé∏îsÇµÇ‹ÇµÇΩÅB");
		for (int i = 0; i != element.size(); i++)
		{
			int n;
			stringstream ss;
			ss << element[i];
			switch (i)
			{
			case 0:
				ss >> width;
				break;
			case 1:
				ss >> height;
				break;
			case 2:
				ss >> x;
				break;
			case 3:
				ss >> y;
				break;
			case 4:
				ss >> n;
				dispAddFlag.push_back(n == 1 ? true : false);
				break;
			}
		}

		widthList.push_back(width);
		heightList.push_back(height);
		xList.push_back(x);
		yList.push_back(y);
		graphNumList.push_back(x*y);
	}

	ifs.close();
	
	for (int i = 0; i != widthList.size(); i++)
	{
		stringstream ss;
		ss << "data/graph/character/object/object" << Function::NumToStringFillZero(i, 2) << ".png";
		int result = LoadDivGraph(ss.str().c_str(), xList[i] * yList[i], xList[i], yList[i], widthList[i], heightList[i], graph[i]);

		assert(result == 0 && "ObjectMap::Load()Ç…ÇƒâÊëúÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩ(1)ÅB");
	}

	ifs.open("data/csv/object/objectInfo.csv");
	assert(!ifs.fail() && "ObjectMap::Load()Ç…Çƒé∏îsÇµÇ‹ÇµÇΩÅB");
	getline(ifs, str);

	while(getline(ifs, str))
	{
		auto element = Function::split(str, ',');
		assert(element.size() == 8 && "ObjectMap::Load() ÉTÉCÉYÇ™ïsê≥Ç≈Ç∑ÅB");

		for (int k = 0; k != element.size(); k++)
		{
			int num;
			stringstream ss;
			ss << element[k];
			switch (k)
			{
			case 0:
				ss >> num;
				graphKindList.push_back(num);
				break;
			case 1:
				ss >> num;
				canDestroyList.push_back(num == 1 ? true : false);
				break;
			case 2:
				ss >> num;
				canThroughList.push_back(num == 1 ? true : false);
				break;
			case 3:
				ss >> num;
				durabilityList.push_back(num);
				break;
			case 4:
				ss >> num;
				hardnessList.push_back(num);
				break;
			case 5:
			{
				auto element2 = Function::split(ss.str(), '|');
				vector<int> tempDropItemList;
				for (int j = 0; j != element2.size(); j++)
				{
					int num;
					stringstream ss2;
					ss2 << element2[j];
					ss2 >> num;
					tempDropItemList.push_back(num);
				}
				dropItemList.push_back(tempDropItemList);
			}
			break;
			case 6:
			{
				auto element2 = Function::split(ss.str(), '|');
				vector<int> tempDropRateList;
				for (int j = 0; j != element2.size(); j++)
				{
					int num;
					stringstream ss2;
					ss2 << element2[j];
					ss2 >> num;
					tempDropRateList.push_back(num);
				}
				dropRateList.push_back(tempDropRateList);
			}
				break;
			case 7:
				ss >> num;
				dispMiniMapList.push_back(num);
				break;
			}
		}
	}

	ifs.close();
}

void ObjectMap::Update()
{
	UpdateAnimationTimer();
}

void ObjectMap::UpdateAnimationTimer()
{
	animationTimer++;
}

void ObjectMap::CauseByPlayer(int sourceID, int skillKind, bool SPMAX)
{
	int value;

	switch (skillKind)
	{
	case 100:
		value = max(0, (playerData->GetCharacterStatusList()[sourceID]->GetATK()*playerData->GetCharacterStatusList()[sourceID]->GetNormalMagnification()*(1 + (playerData->GetCharacterStatusList()[sourceID]->GetLv() - 1)*0.04)));
		if (SPMAX)
		{
			double damagePercent = 1.0;
			for (auto n : playerData->GetCharacterStatusList()[sourceID]->GetAccessory())
			{
				if (n != -1)
				{
					if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT] > 0.001)
					{
						damagePercent *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT];
					}
				}
			}
			value *= damagePercent;
			value = max(0, value);
		}
		break;
	case 101:
		value = max(0, (playerData->GetCharacterStatusList()[sourceID]->GetINT()*playerData->GetCharacterStatusList()[sourceID]->GetNormalMagnification()*(1 + (playerData->GetCharacterStatusList()[sourceID]->GetLv() - 1)*0.04)));
		value *= 0.7;
		if (SPMAX)
		{
			double damagePercent = 1.0;
			for (auto n : playerData->GetCharacterStatusList()[sourceID]->GetAccessory())
			{
				if (n != -1)
				{
					if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT] > 0.001)
					{
						damagePercent *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT];
					}
				}
			}
			value *= damagePercent;
			value = max(0, value);
		}
		break;
	default:
		if (CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].attribute[(int)PlayerSkillAttribute::TYPE] == 0)
		{
			value = max(0, (playerData->GetCharacterStatusList()[sourceID]->GetATK()*playerData->GetCharacterStatusList()[sourceID]->GetSkillMagnification()*(1 + (playerData->GetCharacterStatusList()[sourceID]->GetLv() - 1)*0.04)));
		}
		else
		{
			value = max(0, (playerData->GetCharacterStatusList()[sourceID]->GetINT()*playerData->GetCharacterStatusList()[sourceID]->GetSkillMagnification()*(1 + (playerData->GetCharacterStatusList()[sourceID]->GetLv() - 1)*0.04)));
		}
		value *= CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].value[playerData->GetCharacterStatusList()[sourceID]->GetSkillLevel()[skillKind] - 1];
		if (SPMAX)
		{
			double damagePercent = 1.0;
			for (auto n : playerData->GetCharacterStatusList()[sourceID]->GetAccessory())
			{
				if (n != -1)
				{
					if (ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT] > 0.001)
					{
						damagePercent *= ItemInfoList::GetItemInfoList()[n].option[(int)ItemInfo::ItemOption::RAISE_DAMAGE_WHEN_MAX_SP_PERCENT];
					}
				}
			}
			value *= damagePercent;
			value = max(0, value);
		}
		break;
	}

	value -= hardnessList[kind];

	value = max(value, 0);
	durability -= value;

	durability = max(durability, 0);

	if (durability == 0)
	{
		deathFlag = true;
	}

	if (skillKind == 100 || skillKind == 101 || CharacterSkillInfoList::GetCharacterSkillInfoList()[skillKind].type == SkillType::ATTACK)
	{
		textUIList.push_back(make_shared<DamageText>(camera, position, value));
	}
}

void ObjectMap::Death()
{
	assert(kind != -1 && "ObjectMap::Death()");

	vector<int> dropItem;

	if (dropItemList[kind][0] != -1)
	{
		for (int i = 0; i != dropItemList[kind].size(); i++)
		{
			int rand = (GetRand(10000) % 100) + 1;
			if (rand <= dropRateList[kind][i])
			{
				dropItem.push_back(dropItemList[kind][i]);
			}
		}
	}

	if (dropItem.size() != 0)
	{
		dropItemMapList.push_back(make_shared<DropItem>(dropItem, masuPosition, camera));
	}
}

void ObjectMap::Draw()
{
	if (dispAddFlag[graphKindList[kind]])
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	}
	DrawRotaGraphF(position.x - camera.x, position.y - camera.y, 1.0, 0.0, graph[graphKindList[kind]][(animationTimer / 3) % graphNumList[graphKindList[kind]]], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}