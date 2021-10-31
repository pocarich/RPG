#pragma once

#include"Define.h"
#include"Class.h"
#include"PlayerData.h"
#include"TextUI.h"

class ObjectMap
{
protected:
	static GHandle graph[15][30];
	static vector<int> graphNumList;
	static vector<bool> dispAddFlag;
	static vector<int> graphKindList;
	static vector<bool> canDestroyList;
	static vector<bool> canThroughList;
	static vector<int> durabilityList;	//‘Ï‹v’l
	static vector<int> hardnessList;
	static vector<vector<int>> dropItemList;
	static vector<vector<int>> dropRateList;
	static vector<int> dispMiniMapList;
protected:
	PlayerData* playerData;
	PlayerMap* playerMap;
	list<TextUIPtr>& textUIList;
	list<BattleEffectPtr>& battleEffectList;
	list<BossMapPtr>& bossMapList;
	list<ObjectMapPtr>& objectMapList;
	list<PeopleMapPtr>& peopleMapList;
	list<EnemyMapPtr>& enemyMapList;
	list<DropItemPtr>& dropItemMapList;
	int& mapNum;
	int kind;
	int animationTimer;
	Vector2<int> masuPosition;
	Vector2<double>& camera;
	Vector2<double> position;
	int durability;
	bool deathFlag;
protected:
	void UpdateAnimationTimer();
public:
	ObjectMap(int kind,Vector2<int> masuPosition,PlayerData* playerData, PlayerMap* playerMap, list<TextUIPtr>& textUIList, list<BattleEffectPtr>& battleEffectList, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<PeopleMapPtr>& peopleMapList, list<EnemyMapPtr>& enemyMapList, list<DropItemPtr>& dropItemMapList, int& mapNum, Vector2<double>& camera);
	virtual ~ObjectMap();
	static void Load();
	virtual void Update();
	virtual void Draw();
	void CauseByPlayer(int sourceID, int skillKind, bool SPMAX);
	void Death();
	int GetKind()const { return kind; }
	Vector2<int> GetMasuPosition()const { return masuPosition; }
	Vector2<double> GetPosition()const { return position; }
	int GetDurability()const { return durability; }
	bool GetDeathFlag()const { return deathFlag; }
	int GetGraphKind()const { return graphKindList[kind]; }
	bool GetCanDestroy()const { return canDestroyList[kind]; }
	bool GetCanThrough()const { return canThroughList[kind]; }
	int GetMaxDurability()const { return durabilityList[kind]; }
	int GetHardness()const { return hardnessList[kind]; }
	const vector<int>& GetDropItem()const { return dropItemList[kind]; }
	const vector<int>& GetDropRate()const { return dropRateList[kind]; }
	int GetDispMiniMap()const { return dispMiniMapList[kind]; }
};