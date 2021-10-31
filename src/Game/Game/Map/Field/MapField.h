#pragma once

#include"Define.h"
#include"Class.h"
#include"PlayerMap.h"

class MapField
{
private:
	static GHandle mapBackChip[20 * 30];
	static GHandle mapObjectChip[20 * 20];
	static GHandle pointer;
	int pointerCounter;
	int kirakiraCounter;
private:
	int& mapNum;
	Vector2<double>& camera;
	PlayerMap* playerMap;
private:
	void UpdatePointerCounter();
public:
	static void Load();
	MapField(PlayerMap* playerMap,int& mapNum,Vector2<double>& camera);
	~MapField();
	void Update();
	void Draw();
};