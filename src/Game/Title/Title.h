#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"
#include"Class.h"
#include"SaveData.h"

class Title
{
private:
	static GHandle mapBackChip[20 * 30];
	static GHandle mapObjectChip[20 * 20];
private:
	int state;
	bool stateEndFlag;
	bool pushStartFlag;
	bool backFlag;
	int timer;
	int darkAlpha;
	int loadDataNum;
	int cursorNum1;
	int cursorNum2;
	array<SaveData, Define::SAVE_DATA_NUM>& saveDataList;
	Vector2<int> camera;
private:
	void Move();
	void Push();
	void Update();
	void Draw();
public:
	Title(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList);
	~Title();
	static void Load();
	void Main();
	bool GetStateEndFlag()const { return stateEndFlag; }
	int GetLoadDataNum()const { return loadDataNum; }
};