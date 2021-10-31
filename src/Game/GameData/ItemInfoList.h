#pragma once

#include"Define.h"
#include"ItemInfo.h"

class ItemInfoList
{
	static vector<ItemInfo> itemInfoList;
	static GHandle graph[Define::ITEM_ICON_KIND + 1];
public:
	static void Load();
	static const vector<ItemInfo>& GetItemInfoList() { return itemInfoList; }
	static const GHandle* GetGraph() { return graph; }
};