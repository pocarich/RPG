
/*   カラーコード管理   */

#pragma once

#include"Define.h"

class ColorMgr
{
public:
	enum struct BaseColor
	{
		WHITE,
		BLACK,
		GRAY,
		RED,
		BLUE,
		GREEN,
		YELLOW,
		PURPLE,
		PINK,
		ORANGE,
		BROWN,
		LIGHTGREEN,
		LIGHTBLUE,
		SIZE
	};

	enum struct CustomColor
	{
		COLOR1 = (int)BaseColor::SIZE,
		SIZE
	};

private:
	static vector<Color> colorList;
private:                             
	ColorMgr() {};
	ColorMgr(const ColorMgr&) {};
	ColorMgr& operator =(const ColorMgr&) {};
public:
	static void Load();
	static const vector<Color>& GetColorCode(){ return colorList; }
};

