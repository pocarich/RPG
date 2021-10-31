#pragma once

#include"Define.h"
#include"SystemMessage.h"
#include"PlayerData.h"
#include"MapUI.h"
#include"PlayerMap.h"

class UI
{
private:
	static GHandle keyGraph[4];
	static GHandle conditionErrorGraph[(int)ConditionError::SIZE];
private:
	PlayerData* playerData;
	PlayerMap* playerMap;
	list<EnemyMapPtr>& enemyMapList;
	list<BossMapPtr>& bossMapList;
	list<ObjectMapPtr>& objectMapList;
	list<PeopleMapPtr>& peopleMapList;
	list<DropItemPtr>& dropItemMapList;
	SystemMessage* systemMessage;
	MapUI* mapUI;
	int& mapNum;
	bool showFlag;
private:
	void DrawCharacterStatus();
	void DrawOperation();
	void PushQ();
public:
	UI(PlayerMap* playerMap,PlayerData* playerData, list<EnemyMapPtr>& enemyMapList, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<PeopleMapPtr>& peopleMapList, list<DropItemPtr>& dropItemMapList,SystemMessage* systemMessage,int& mapNum);
	~UI();
	static void Load();
	void Update();
	void Draw();
	void ChangeMap();
};