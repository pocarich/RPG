#pragma once

#include"Define.h"
#include"Class.h"

class DropItem
{
private:
	static GHandle graph;
private:
	vector<int> itemList;
	Vector2<int> masuPosition;
	Vector2<double>& camera;
	bool deleteFlag;
public:
	DropItem(vector<int> itemList, Vector2<int> masuPosition,Vector2<double>& camera);
	static void Load();
	void Update();
	void Draw();
	void Picked();
	const vector<int>& GetItemList()const { return itemList; }
	Vector2<int> GetMasuPosition()const { return masuPosition; }
	bool GetDeleteFlag()const { return deleteFlag; }
};