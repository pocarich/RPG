#pragma once

#include"MapInfo.h"
#include"Singleton.h"

class MapInfoList :public Singleton
{
	static vector<MapInfo> mapInfoList;
	static vector<int> cannotThroughUp;
	static vector<int> cannotThroughRight;
	static vector<int> cannotThroughLeft;
	static vector<int> cannotThroughDown;
	static vector<int> cannotThroughUpObject;
	static vector<int> cannotThroughRightObject;
	static vector<int> cannotThroughLeftObject;
	static vector<int> cannotThroughDownObject;
public:
	static void Load();
	static vector<MapInfo>& GetMapInfoList() { return mapInfoList; }
	static const vector<int>& GetCannotThroughUp() { return cannotThroughUp; }
	static const vector<int>& GetCannotThroughRight() { return cannotThroughRight; }
	static const vector<int>& GetCannotThroughLeft() { return cannotThroughLeft; }
	static const vector<int>& GetCannotThroughDown() { return cannotThroughDown; }
	static const vector<int>& GetCannotThroughUpObject() { return cannotThroughUpObject; }
	static const vector<int>& GetCannotThroughRightObject() { return cannotThroughRightObject; }
	static const vector<int>& GetCannotThroughLeftObject() { return cannotThroughLeftObject; }
	static const vector<int>& GetCannotThroughDownObject() { return cannotThroughDownObject; }
};