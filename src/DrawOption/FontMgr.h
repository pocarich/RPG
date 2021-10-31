
/*   ƒtƒHƒ“ƒgŠÇ—   */

#pragma once

#include"Define.h"

class FontMgr
{
	static vector<Font> fontList;
private:
	FontMgr() {};
	FontMgr(const FontMgr&) {};
	FontMgr& operator =(const FontMgr&) {};
public:
	static void Load();
	static const vector<Font>& GetFont() { return fontList; }
};

