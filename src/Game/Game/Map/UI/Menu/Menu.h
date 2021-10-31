#pragma once

#include"Define.h"
#include"PlayerData.h"
#include"MenuTop.h"
#include"MenuItem.h"
#include"MenuSkill.h"
#include"MenuEquip.h"
#include"MenuSave.h"
#include"MenuSynthesis.h"
#include"MenuAchievement.h"
#include"MenuTitle.h"

class Menu
{
private:
	enum struct MenuState
	{
		TOP,
		ITEM,
		SKILL,
		EQUIP,
		SYNTHESIS,
		ACHIEVEMENT,
		SAVE,
		TITLE
	};
private:
	MenuState menuState;
	PlayerData* playerData;
	MenuTop* menuTop;
	MenuItem* menuItem;
	MenuSkill* menuSkill;
	MenuEquip* menuEquip;
	MenuSave* menuSave;
	MenuSynthesis* menuSynthesis;
	MenuAchievement* menuAchievement;
	MenuTitle* menuTitle;
	bool closeFlag;
	array<SaveData, Define::SAVE_DATA_NUM>& saveDataList;
	int& mapNum;
	bool canSave;
private:
	void UpdateState();
public:
	Menu(PlayerData* playerData, array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int& mapNum, bool canSave);
	~Menu();
	void Update();
	void Draw();
	void ResetSaveDataNum() { menuSave->ResetSaveDataNum(); }

	bool GetCloseFlag()const { return closeFlag; }
	int GetSaveDataNum()const;
	bool GetEndFlag()const;
};