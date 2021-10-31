#pragma once

#include"../header/Define.h"

#include"../header/Map.h"
#include"PlayerData.h"
#include"SpecialEvent.h"
#include"SaveData.h"

class Game
{
public:
	enum struct GameState
	{
		MAP,
		EVENT
	};
private:
	Map* map;
	PlayerData* playerData;
	SpecialEvent* specialEvent;

	GameState state;
	bool stateEndFlag;
	int playTime;
	int specialEventNum;
	int loadDataNum;
	array<SaveData, Define::SAVE_DATA_NUM>& saveDataList;
private:
	void UpdatePlayTime();
	void MapFunc();
	void HappenEvent();
	void EventFunc();
	void Save();
public:
	Game(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList,int loadDataNum);
	~Game();
	void Main();
	void ResetSaveDataNum() { map->ResetSaveDataNum(); }
	void Save(int saveDataNum);
	bool GetStateEndFlag()const;
	int GetSaveDataNum()const;
};