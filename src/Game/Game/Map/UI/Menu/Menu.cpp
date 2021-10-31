#include"../header/Menu.h"

Menu::Menu(PlayerData* playerData, array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int& mapNum, bool canSave) :playerData(playerData), saveDataList(saveDataList), mapNum(mapNum), canSave(canSave)
{
	menuState = MenuState::TOP;
	closeFlag = false;
	menuTop = nullptr;
	menuItem = nullptr;
	menuSkill = nullptr;
	menuEquip = nullptr;
	menuSave = nullptr;
	menuSynthesis = nullptr;
	menuAchievement = nullptr;
	menuTitle = nullptr;
}

Menu::~Menu()
{
	if (menuTop != nullptr)
	{
		delete menuTop;
	}
	if (menuItem != nullptr)
	{
		delete menuItem;
	}
	if (menuSkill != nullptr)
	{
		delete menuSkill;
	}
	if (menuEquip != nullptr)
	{
		delete menuEquip;
	}
	if (menuSave != nullptr)
	{
		delete menuSave;
	}
	if (menuSynthesis != nullptr)
	{
		delete menuSynthesis;
	}
	if (menuAchievement != nullptr)
	{
		delete menuAchievement;
	}
	if (menuTitle != nullptr)
	{
		delete menuTitle;
	}
}

void Menu::Update()
{
	switch (menuState)
	{
	case MenuState::TOP:
		if (menuTop == nullptr)
		{
			menuTop = new MenuTop(playerData,canSave);
		}
		menuTop->Update();
		break;
	case MenuState::ITEM:
		if (menuItem == nullptr)
		{
			menuItem = new MenuItem(playerData);
		}
		menuItem->Update();
		break;
	case MenuState::SKILL:
		if (menuSkill == nullptr)
		{
			menuSkill = new MenuSkill(playerData);
		}
		menuSkill->Update();
		break;
	case MenuState::EQUIP:
		if (menuEquip == nullptr)
		{
			menuEquip = new MenuEquip(playerData);
		}
		menuEquip->Update();
		break;
	case MenuState::SYNTHESIS:
		if (menuSynthesis == nullptr)
		{
			menuSynthesis = new MenuSynthesis(playerData);
		}
		menuSynthesis->Update();
		break;
	case MenuState::ACHIEVEMENT:
		if (menuAchievement == nullptr)
		{
			menuAchievement = new MenuAchievement(playerData);
		}
		menuAchievement->Update();
		break;
	case MenuState::SAVE:
		if (menuSave == nullptr)
		{
			menuSave = new MenuSave(playerData,saveDataList,mapNum);
		}
		menuSave->Update();
		break;
	case MenuState::TITLE:
		if (menuTitle == nullptr)
		{
			menuTitle = new MenuTitle(playerData);
		}
		menuTitle->Update();
	}
	UpdateState();
}

void Menu::UpdateState()
{
	switch (menuState)
	{
	case MenuState::TOP:
		if (menuTop->GetCloseFlag())
		{
			closeFlag = true;
		}
		if (menuTop->GetPushFlag())
		{
			menuTop->Reset();
			switch (menuTop->GetTopic())
			{
			case MenuTop::Topic::ITEM:
				menuState = MenuState::ITEM;
				break;
			case MenuTop::Topic::SKILL:
				menuState = MenuState::SKILL;
				break;
			case MenuTop::Topic::EQUIP:
				menuState = MenuState::EQUIP;
				break;
			case MenuTop::Topic::SYNTHESIS:
				menuState = MenuState::SYNTHESIS;
				break;
			case MenuTop::Topic::ACHIEVEMENT:
				menuState = MenuState::ACHIEVEMENT;
				break;
			case MenuTop::Topic::SAVE:
				menuState = MenuState::SAVE;
				break;
			case MenuTop::Topic::TITLE:
				menuState = MenuState::TITLE;
				break;
			}
		}
		break;
	case MenuState::ITEM:
		if (menuItem == nullptr)
		{
			menuItem = new MenuItem(playerData);
		}
		if (menuItem->GetCloseFlag())
		{
			delete menuItem;
			menuItem = nullptr;
			menuState = MenuState::TOP;
		}
		break;
	case MenuState::SKILL:
		if (menuSkill == nullptr)
		{
			menuSkill = new MenuSkill(playerData);
		}
		if (menuSkill->GetCloseFlag())
		{
			delete menuSkill;
			menuSkill = nullptr;
			menuState = MenuState::TOP;
		}
		break;
	case MenuState::EQUIP:
		if (menuEquip == nullptr)
		{
			menuEquip = new MenuEquip(playerData);
		}
		if (menuEquip->GetCloseFlag())
		{
			delete menuEquip;
			menuEquip = nullptr;
			menuState = MenuState::TOP;
		}
		break;
	case MenuState::SYNTHESIS:
		if (menuSynthesis == nullptr)
		{
			menuSynthesis = new MenuSynthesis(playerData);
		}
		if (menuSynthesis->GetCloseFlag())
		{
			delete menuSynthesis;
			menuSynthesis = nullptr;
			menuState = MenuState::TOP;
		}
		break;
	case MenuState::ACHIEVEMENT:
		if (menuAchievement == nullptr)
		{
			menuAchievement = new MenuAchievement(playerData);
		}
		if (menuAchievement->GetCloseFlag())
		{
			delete menuAchievement;
			menuAchievement = nullptr;
			menuState = MenuState::TOP;
		}
		break;
	case MenuState::SAVE:
		if (menuSave == nullptr)
		{
			menuSave = new MenuSave(playerData,saveDataList, mapNum);
		}
		if (menuSave->GetCloseFlag())
		{
			delete menuSave;
			menuSave = nullptr;
			menuState = MenuState::TOP;
		}
		break;
	case MenuState::TITLE:
		if (menuTitle == nullptr)
		{
			menuTitle = new MenuTitle(playerData);
		}
		if (menuTitle->GetCloseFlag())
		{
			delete menuTitle;
			menuTitle = nullptr;
			menuState = MenuState::TOP;
		}
		break;
	}
}

void Menu::Draw()
{
	switch (menuState)
	{
	case MenuState::TOP:
		if (menuTop == nullptr)
		{
			menuTop = new MenuTop(playerData,canSave);
		}
		menuTop->Draw();
		break;
	case MenuState::ITEM:
		if (menuItem == nullptr)
		{
			menuItem = new MenuItem(playerData);
		}
		menuItem->Draw();
		break;
	case MenuState::SKILL:
		if (menuSkill == nullptr)
		{
			menuSkill = new MenuSkill(playerData);
		}
		menuSkill->Draw();
		break;
	case MenuState::EQUIP:
		if (menuEquip == nullptr)
		{
			menuEquip = new MenuEquip(playerData);
		}
		menuEquip->Draw();
		break;
	case MenuState::SYNTHESIS:
		if (menuSynthesis == nullptr)
		{
			menuSynthesis = new MenuSynthesis(playerData);
		}
		menuSynthesis->Draw();
		break;
	case MenuState::ACHIEVEMENT:
		if (menuAchievement == nullptr)
		{
			menuAchievement = new MenuAchievement(playerData);
		}
		menuAchievement->Draw();
		break;
	case MenuState::SAVE:
		if (menuSave == nullptr)
		{
			menuSave = new MenuSave(playerData, saveDataList, mapNum);
		}
		menuSave->Draw();
		break;
	case MenuState::TITLE:
		if (menuTitle == nullptr)
		{
			menuTitle = new MenuTitle(playerData);
		}
		menuTitle->Draw();
		break;
	}
}

int Menu::GetSaveDataNum()const
{
	if (menuSave != nullptr)
	{
		return menuSave->GetSaveDataNum();
	}

	return -1;
}

bool Menu::GetEndFlag()const
{
	if (menuTitle != nullptr)
	{
		return menuTitle->GetGoTitle();
	}
	return false;
}