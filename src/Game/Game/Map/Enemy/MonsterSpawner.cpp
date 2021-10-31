#include"../header/MonsterSpawner.h"
#include"../header/MapInfoList.h"
#include"../header/BossSpawnInfoList.h"

#include"../header/EnemyMap000.h"
#include"../header/EnemyMap001.h"
#include"../header/EnemyMap002.h"
#include"../header/EnemyMap003.h"
#include"../header/EnemyMap004.h"
#include"../header/EnemyMap005.h"
#include"../header/EnemyMap006.h"
#include"../header/EnemyMap007.h"
#include"../header/EnemyMap008.h"
#include"../header/EnemyMap009.h"
#include"../header/EnemyMap010.h"
#include"../header/EnemyMap011.h"
#include"../header/EnemyMap012.h"
#include"../header/EnemyMap013.h"
#include"../header/EnemyMap014.h"
#include"../header/EnemyMap015.h"
#include"../header/EnemyMap016.h"
#include"../header/EnemyMap017.h"
#include"../header/EnemyMap018.h"
#include"../header/EnemyMap019.h"
#include"../header/EnemyMap020.h"
#include"../header/EnemyMap021.h"
#include"../header/EnemyMap022.h"
#include"../header/EnemyMap023.h"
#include"../header/EnemyMap024.h"
#include"../header/EnemyMap025.h"
#include"../header/EnemyMap026.h"
#include"../header/EnemyMap027.h"
#include"../header/EnemyMap028.h"
#include"../header/EnemyMap029.h"
#include"../header/EnemyMap030.h"
#include"../header/EnemyMap031.h"
#include"../header/EnemyMap032.h"
#include"../header/EnemyMap033.h"
#include"../header/EnemyMap034.h"
#include"../header/EnemyMap035.h"
#include"../header/EnemyMap036.h"
#include"../header/EnemyMap037.h"
#include"../header/EnemyMap038.h"
#include"../header/EnemyMap039.h"
#include"../header/EnemyMap040.h"
#include"../header/EnemyMap041.h"
#include"../header/EnemyMap042.h"
#include"../header/EnemyMap043.h"
#include"../header/EnemyMap044.h"

#include"../header/ObjectMap000.h"

#include"../header/BossMap000.h"
#include"../header/BossMap001.h"
#include"../header/BossMap002.h"
#include"../header/BossMap003.h"
#include"../header/BossMap008.h"

MonsterSpawner::MonsterSpawner(PlayerData* playerData, PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList, list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList, int& mapNum, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList) :textUIList(textUIList), playerData(playerData), playerMap(playerMap), peopleMapList(peopleMapList), enemyMapList(enemyMapList), mapNum(mapNum), camera(camera), battleEffectList(battleEffectList), dropItemList(dropItemList), bossMapList(bossMapList), objectMapList(objectMapList)
{
	for (int i = 0; i < Define::ENEMY_MAX; i++)
	{
		spawnTimer[i] = 0;
		exist[i] = false;
	}
}

MonsterSpawner::~MonsterSpawner()
{

}

void MonsterSpawner::Update()
{
	assert(MapInfoList::GetMapInfoList()[mapNum].monsterPopPositionList.size() < Define::ENEMY_MAX&&"MonsterSpawner::Update()");
	Spawn();
	BossSpawn();
	CheckExist();
}

void MonsterSpawner::BossSpawn()
{
	int i = 0;
	for (auto& info : BossSpawnInfoList::GetBossSpawnInfoList())
	{
		if (info.mapNum == mapNum && find_if(bossMapList.begin(), bossMapList.end(), [&](BossMapPtr& obj) {return obj->GetID() == i; }) == bossMapList.end())
		{
			bool isPopPosition = false;
			bool canPop = false;

			if (info.popPlayerPosition == Vector2<int>(0, 0))
			{
				isPopPosition = true;
			}
			else if (info.popPlayerPosition == playerMap->GetMasuPosition())
			{
				isPopPosition = true;
			}
			else
			{
				isPopPosition = false;
			}
			if (info.noPopFlag != -1 && playerData->GetFlagList()[info.noPopFlag])
			{
				canPop = false;
			}
			else
			{
				if (info.popFlag == -1)
				{
					canPop = true;
				}
				else if (playerData->GetFlagList()[info.popFlag])
				{
					canPop = true;
				}
				else
				{
					canPop = false;
				}
			}

			if (isPopPosition&&canPop)
			{
				switch (info.bossKind)
				{
				case 0:
					bossMapList.push_back(make_shared<BossMap000>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, battleEffectList, textUIList, dropItemList, i, info.popBossPosition, camera, mapNum, info.standFlag,info.specialEventNum));
					break;
				case 1:
					bossMapList.push_back(make_shared<BossMap001>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, battleEffectList, textUIList, dropItemList, i, info.popBossPosition, camera, mapNum, info.standFlag, info.specialEventNum));
					break;
				case 2:
					bossMapList.push_back(make_shared<BossMap002>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, battleEffectList, textUIList, dropItemList, i, info.popBossPosition, camera, mapNum, info.standFlag, info.specialEventNum));
					break;
				case 3:
					bossMapList.push_back(make_shared<BossMap003>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, battleEffectList, textUIList, dropItemList, i, info.popBossPosition, camera, mapNum, info.standFlag, info.specialEventNum));
					break;
				case 8:
					bossMapList.push_back(make_shared<BossMap008>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, battleEffectList, textUIList, dropItemList, i, info.popBossPosition, camera, mapNum, info.standFlag, info.specialEventNum));
					break;
				}

				for (int i = 0; i != info.popObjectKind.size(); i++)
				{
					switch (info.popObjectKind[i])
					{
					case 0:
						objectMapList.push_back(make_shared<ObjectMap000>(info.popObjectPosition[i], playerData, playerMap, textUIList, battleEffectList, bossMapList, objectMapList, peopleMapList, enemyMapList, dropItemList, mapNum, camera));
						break;
					}
				}
			}
		}
		i++;
	}
}

void MonsterSpawner::CheckExist()
{
	vector<int> existIDList;

	for (int i = 0; i < Define::ENEMY_MAX; i++)
	{
		exist[i] = false;
	}

	for (auto enemyPtr : enemyMapList)
	{
		existIDList.push_back(enemyPtr->GetID());
	}

	for (auto n : existIDList)
	{
		exist[n] = true;
	}
}

void MonsterSpawner::UpdateTimer()
{
	
}

void MonsterSpawner::FirstSpawn()
{
	for (int i = 0; i < MapInfoList::GetMapInfoList()[mapNum].monsterPopPositionList.size(); i++)
	{
		Vector2<int> pos = MapInfoList::GetMapInfoList()[mapNum].monsterPopPositionList[i];
		bool inside = 0 <= pos.x&&pos.x < MapInfoList::GetMapInfoList()[mapNum].widthNum && 0 <= pos.y&&pos.y < MapInfoList::GetMapInfoList()[mapNum].heightNum;
		bool nobody = playerMap->GetMasuPosition() != pos&&count_if(enemyMapList.begin(), enemyMapList.end(), [&](EnemyMapPtr& obj) {return obj->GetMasuPosition() == pos; }) == 0;
		bool canThrough = MapInfoList::GetMapInfoList()[mapNum].canThrough[pos.y][pos.x];
		if (inside&&nobody&&canThrough)
		{
			spawnTimer[i] = 0;
			exist[i] = true;
			int enemyKind = GetRand(1000) % MapInfoList::GetMapInfoList()[mapNum].monsterKindList.size();

			switch (MapInfoList::GetMapInfoList()[mapNum].monsterKindList[enemyKind])
			{
			case 0:
				enemyMapList.push_back(make_shared<EnemyMap000>(playerData,playerMap,bossMapList,objectMapList,enemyMapList,peopleMapList,i, pos, camera, battleEffectList,textUIList, dropItemList,mapNum));
				break;
			case 1:
				enemyMapList.push_back(make_shared<EnemyMap001>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 2:
				enemyMapList.push_back(make_shared<EnemyMap002>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 3:
				enemyMapList.push_back(make_shared<EnemyMap003>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 4:
				enemyMapList.push_back(make_shared<EnemyMap004>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 5:
				enemyMapList.push_back(make_shared<EnemyMap005>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 6:
				enemyMapList.push_back(make_shared<EnemyMap006>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 7:
				enemyMapList.push_back(make_shared<EnemyMap007>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 8:
				enemyMapList.push_back(make_shared<EnemyMap008>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 9:
				enemyMapList.push_back(make_shared<EnemyMap009>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 10:
				enemyMapList.push_back(make_shared<EnemyMap010>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 11:
				enemyMapList.push_back(make_shared<EnemyMap011>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 12:
				enemyMapList.push_back(make_shared<EnemyMap012>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 13:
				enemyMapList.push_back(make_shared<EnemyMap013>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 14:
				enemyMapList.push_back(make_shared<EnemyMap014>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 15:
				enemyMapList.push_back(make_shared<EnemyMap015>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 16:
				enemyMapList.push_back(make_shared<EnemyMap016>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 17:
				enemyMapList.push_back(make_shared<EnemyMap017>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 18:
				enemyMapList.push_back(make_shared<EnemyMap018>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 19:
				enemyMapList.push_back(make_shared<EnemyMap019>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 20:
				enemyMapList.push_back(make_shared<EnemyMap020>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 21:
				enemyMapList.push_back(make_shared<EnemyMap021>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 22:
				enemyMapList.push_back(make_shared<EnemyMap022>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 23:
				enemyMapList.push_back(make_shared<EnemyMap023>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 24:
				enemyMapList.push_back(make_shared<EnemyMap024>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 25:
				enemyMapList.push_back(make_shared<EnemyMap025>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 26:
				enemyMapList.push_back(make_shared<EnemyMap026>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 27:
				enemyMapList.push_back(make_shared<EnemyMap027>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 28:
				enemyMapList.push_back(make_shared<EnemyMap028>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 29:
				enemyMapList.push_back(make_shared<EnemyMap029>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 30:
				enemyMapList.push_back(make_shared<EnemyMap030>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 31:
				enemyMapList.push_back(make_shared<EnemyMap031>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 32:
				enemyMapList.push_back(make_shared<EnemyMap032>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 33:
				enemyMapList.push_back(make_shared<EnemyMap033>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 34:
				enemyMapList.push_back(make_shared<EnemyMap034>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 35:
				enemyMapList.push_back(make_shared<EnemyMap035>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 36:
				enemyMapList.push_back(make_shared<EnemyMap036>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 37:
				enemyMapList.push_back(make_shared<EnemyMap037>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 38:
				enemyMapList.push_back(make_shared<EnemyMap038>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 39:
				enemyMapList.push_back(make_shared<EnemyMap039>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 40:
				enemyMapList.push_back(make_shared<EnemyMap040>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 41:
				enemyMapList.push_back(make_shared<EnemyMap041>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 42:
				enemyMapList.push_back(make_shared<EnemyMap042>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 43:
				enemyMapList.push_back(make_shared<EnemyMap043>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			case 44:
				enemyMapList.push_back(make_shared<EnemyMap044>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
				break;
			}
		}
	}
}

void MonsterSpawner::Spawn()
{
	for (int i = 0; i < MapInfoList::GetMapInfoList()[mapNum].monsterPopPositionList.size(); i++)
	{
		if (!exist[i])
		{
			spawnTimer[i]++;
			if (spawnTimer[i] >= Define::ENEMY_REPOP_TIME)
			{
				Vector2<int> pos = MapInfoList::GetMapInfoList()[mapNum].monsterPopPositionList[i];
				bool inside = 0 <= pos.x&&pos.x < MapInfoList::GetMapInfoList()[mapNum].widthNum && 0 <= pos.y&&pos.y < MapInfoList::GetMapInfoList()[mapNum].heightNum;
				bool nobody = playerMap->GetMasuPosition() != pos&&count_if(enemyMapList.begin(), enemyMapList.end(), [&](EnemyMapPtr& obj) {return obj->GetMasuPosition() == pos; }) == 0;
				bool canThrough = MapInfoList::GetMapInfoList()[mapNum].canThrough[pos.y][pos.x];
				if (inside&&nobody&&canThrough)
				{
					spawnTimer[i] = 0;
					exist[i] = true;
					int enemyKind = GetRand(1000) % MapInfoList::GetMapInfoList()[mapNum].monsterKindList.size();

					switch (MapInfoList::GetMapInfoList()[mapNum].monsterKindList[enemyKind])
					{
					case 0:
						enemyMapList.push_back(make_shared<EnemyMap000>(playerData,playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList,mapNum));
						break;
					case 1:
						enemyMapList.push_back(make_shared<EnemyMap001>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 2:
						enemyMapList.push_back(make_shared<EnemyMap002>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 3:
						enemyMapList.push_back(make_shared<EnemyMap003>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 4:
						enemyMapList.push_back(make_shared<EnemyMap004>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 5:
						enemyMapList.push_back(make_shared<EnemyMap005>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 6:
						enemyMapList.push_back(make_shared<EnemyMap006>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 7:
						enemyMapList.push_back(make_shared<EnemyMap007>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 8:
						enemyMapList.push_back(make_shared<EnemyMap008>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 9:
						enemyMapList.push_back(make_shared<EnemyMap009>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 10:
						enemyMapList.push_back(make_shared<EnemyMap010>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 11:
						enemyMapList.push_back(make_shared<EnemyMap011>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 12:
						enemyMapList.push_back(make_shared<EnemyMap012>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 13:
						enemyMapList.push_back(make_shared<EnemyMap013>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 14:
						enemyMapList.push_back(make_shared<EnemyMap014>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 15:
						enemyMapList.push_back(make_shared<EnemyMap015>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 16:
						enemyMapList.push_back(make_shared<EnemyMap016>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 17:
						enemyMapList.push_back(make_shared<EnemyMap017>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 18:
						enemyMapList.push_back(make_shared<EnemyMap018>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 19:
						enemyMapList.push_back(make_shared<EnemyMap019>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 20:
						enemyMapList.push_back(make_shared<EnemyMap020>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 21:
						enemyMapList.push_back(make_shared<EnemyMap021>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 22:
						enemyMapList.push_back(make_shared<EnemyMap022>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 23:
						enemyMapList.push_back(make_shared<EnemyMap023>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 24:
						enemyMapList.push_back(make_shared<EnemyMap024>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 25:
						enemyMapList.push_back(make_shared<EnemyMap025>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 26:
						enemyMapList.push_back(make_shared<EnemyMap026>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 27:
						enemyMapList.push_back(make_shared<EnemyMap027>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 28:
						enemyMapList.push_back(make_shared<EnemyMap028>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 29:
						enemyMapList.push_back(make_shared<EnemyMap029>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 30:
						enemyMapList.push_back(make_shared<EnemyMap030>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 31:
						enemyMapList.push_back(make_shared<EnemyMap031>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 32:
						enemyMapList.push_back(make_shared<EnemyMap032>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 33:
						enemyMapList.push_back(make_shared<EnemyMap033>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 34:
						enemyMapList.push_back(make_shared<EnemyMap034>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 35:
						enemyMapList.push_back(make_shared<EnemyMap035>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 36:
						enemyMapList.push_back(make_shared<EnemyMap036>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 37:
						enemyMapList.push_back(make_shared<EnemyMap037>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 38:
						enemyMapList.push_back(make_shared<EnemyMap038>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 39:
						enemyMapList.push_back(make_shared<EnemyMap039>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 40:
						enemyMapList.push_back(make_shared<EnemyMap040>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 41:
						enemyMapList.push_back(make_shared<EnemyMap041>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 42:
						enemyMapList.push_back(make_shared<EnemyMap042>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 43:
						enemyMapList.push_back(make_shared<EnemyMap043>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					case 44:
						enemyMapList.push_back(make_shared<EnemyMap044>(playerData, playerMap, bossMapList, objectMapList, enemyMapList, peopleMapList, i, pos, camera, battleEffectList, textUIList, dropItemList, mapNum));
						break;
					}
				}
			}
		}
	}
}

void MonsterSpawner::Reset()
{
	for (int i = 0; i < Define::ENEMY_MAX; i++)
	{
		spawnTimer[i] = 0;
		exist[i] = false;
	}
}