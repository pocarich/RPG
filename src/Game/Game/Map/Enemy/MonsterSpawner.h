#pragma once

#include"Define.h"
#include"BattleEffect.h"
#include"PlayerMap.h"
#include"PlayerData.h"
#include"TextUI.h"
#include"PeopleMap.h"

class MonsterSpawner
{
	PlayerData* playerData;
	list<EnemyMapPtr>& enemyMapList;
	PlayerMap* playerMap;
	Vector2<double>& camera;
	list<BattleEffectPtr>& battleEffectList;
	list<PeopleMapPtr>& peopleMapList;
	list<BossMapPtr>& bossMapList;
	list<ObjectMapPtr>& objectMapList;
	list<DropItemPtr>& dropItemList;
	list<TextUIPtr>& textUIList;
	int spawnTimer[Define::ENEMY_MAX];
	bool exist[Define::ENEMY_MAX];
	int& mapNum;
private:
	void Spawn();
	void BossSpawn();
	void UpdateTimer();
	void CheckExist();
public:
	MonsterSpawner(PlayerData* playerData,PlayerMap* playerMap, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<EnemyMapPtr>& enemyMapList, list<PeopleMapPtr>& peopleMapList,list<TextUIPtr>& textUIList, list<DropItemPtr>& dropItemList,int& mapNum, Vector2<double>& camera, list<BattleEffectPtr>& battleEffectList);
	~MonsterSpawner();
	void Update();
	void Reset();
	void FirstSpawn();
};