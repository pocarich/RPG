#pragma once

#include"Define.h"
#include"ShopInfo.h"

class ShopInfoList
{
	static vector<ShopInfo> shopInfoList;
public:
	static void Load();
	static const vector<ShopInfo>& GetShopInfoList() { return shopInfoList; }
};