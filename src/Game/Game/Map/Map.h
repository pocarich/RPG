#pragma once

#include"Define.h"
#include"PlayerMap.h"
#include"MapField.h"
#include"BattleEffect.h"
#include"EnemyMap.h"
#include"MonsterSpawner.h"
#include"PlayerData.h"
#include"SystemMessage.h"
#include"UI.h"
#include"Menu.h"
#include"PeopleMap.h"
#include"Window.h"
#include"TalkMgr.h"
#include"EventMgr.h"
#include"Shop.h"
#include"INN.h"
#include"TextUI.h"
#include"DropItem.h"
#include"BossMap.h"
#include"ObjectMap.h"

class Map
{
private:
	static const int gameOverDelay = 120;
private:
	enum struct MapState
	{
		NON,
		AREACHANGE,
		MENU,
		EVENT,
		TALK,
		SHOP,
		INN
	};
private:
	Vector2<double> camera;
	list<TextUIPtr> textUIList;
	list<WindowPtr> windowList;
	list<DropItemPtr> dropItemList;
	list<BossMapPtr> bossMapList;
	list<ObjectMapPtr> objectMapList;
	TalkMgr* talkMgr;
	EventMgr* eventMgr;
	PlayerMap* playerMap;
	MapField* mapField;
	PlayerData* playerData;
	Shop* shop;
	INN* _INN;
	SystemMessage* systemMessage;
	UI* ui;
	Menu* menu;
	MonsterSpawner* monsterSpawner;
	list<BattleEffectPtr> battleEffectList;
	list<EnemyMapPtr> enemyMapList;
	list<PeopleMapPtr> peopleMapList;
	MapState mapState;
	int darkAlpha;

	bool areaChangeFlag;
	int areaChangeTimer;
	int specialEventNum;
	int eventInTimer;
	bool eventInFlag;
	bool gameOverFlag;
	int gameOverTimer;

	int nowLv[Define::CHARACTER_NUM];

	array<SaveData, Define::SAVE_DATA_NUM>& saveDataList;
private:
	int mapNum;
private:
	void UpdateGameOver();
	void UpdateCamera();
	void UpdateAreaChange();
	void UpdateMapInfo();
	void DeleteBattleEffect();
	void DeleteEnemy();
	void DeleteTextUI();
	void DeleteDropItem();
	void DeleteObject();
	void DeleteBoss();
	void PushE();
	void OpenMenu();
	void CloseMenu();
	void ChangeMap();
	void PeopleSpawn();
	void ObjectSpawn();
	void UpdateWindowList();
	void UpdateEventIn();
	void EventIn();
	void TalkIn();
	void TalkEnd();
	void EventEnd();
	void ShopEnd();
	void INNEnd();
	void CheckCharacterLv();
public:
	Map(PlayerData* playerData, array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int loadDataNum);
	~Map();
	void Update();
	void Draw();
	void ResetAfterEvent();
	void ResetSaveDataNum() { menu->ResetSaveDataNum(); }
	void Save(int saveDataNum);

	bool GetEventInFlag()const { return eventInFlag; }
	int GetSpecialEventNum()const { return specialEventNum; }
	int GetSaveDataNum()const;
	bool GetEndFlag()const;
};