#pragma once

#include"Class.h"
#include"Define.h"

class TitleMapInfo
{
public:
	static int mapChip[60][Define::WINDOW_WIDTH / Define::MASU_SIZE];
	static int mapObject[60][Define::WINDOW_WIDTH / Define::MASU_SIZE];
public:
	static void Load();
};