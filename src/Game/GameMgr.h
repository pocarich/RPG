#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"
#include"Title.h"
#include"Game.h"
#include"SaveData.h"

enum struct GameState
{
	TITLE,
	GAME
};

class GameMgr
{
	GameState state;
	Title* title;
	Game* game;
	int loadDataNum;
	array<SaveData, Define::SAVE_DATA_NUM> saveDataList;
private:
	void LoadData();
	void Save(int saveDataNum);
	void TitleFunc();
	void GameFunc();
public:
	GameMgr();
	~GameMgr();
	void Main();
};
