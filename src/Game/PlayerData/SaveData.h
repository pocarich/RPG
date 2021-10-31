#pragma once

#include"../header/Define.h"
#include"../header/Class.h"

class SaveData
{
public:
	bool exist;
	int playTime;
	array<bool, Define::RECIPE_NUM> haveRecipe;
	array<bool, Define::ACHIEVE_NUM> achieveFlag;
	array<bool, Define::CHARACTER_NUM> existCharacterFlag;
	array<bool, Define::FLAG_NUM> flagList;

	array<int, Define::CHARACTER_NUM> Lv;
	array<int, Define::CHARACTER_NUM> HP;
	array<int, Define::CHARACTER_NUM> SP;
	array<int, Define::CHARACTER_NUM> EXP;
	array<int, Define::CHARACTER_NUM> weapon;
	array<int, Define::CHARACTER_NUM> head;
	array<int, Define::CHARACTER_NUM> chest;
	array<array<int, 3>, Define::CHARACTER_NUM> accessory;
	array<array<int, 3>, Define::CHARACTER_NUM> setSkill;
	array<array<int, Define::PLAYER_SKILL_MAX>, Define::CHARACTER_NUM> skillLevel;
	array<array<int, Define::PLAYER_SKILL_MAX>, Define::CHARACTER_NUM> skillEXP;

	int money;
	array<int, Define::ITEM_KIND> holdItemList;

	int mapNum;
	int id;
	Vector2<int> masuPosition;
};