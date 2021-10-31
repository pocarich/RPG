#include"../header/Game.h"
#include"../header/BGMMgr.h"
#include"../header/SpecialEventInfoList.h"

#include"../header/SpecialEvent00.h"
#include"../header/SpecialEvent01.h"
#include"../header/SpecialEvent02.h"
#include"../header/SpecialEvent03.h"
#include"../header/SpecialEvent04.h"
#include"../header/SpecialEvent05.h"
#include"../header/SpecialEvent06.h"
#include"../header/SpecialEvent07.h"
#include"../header/SpecialEvent08.h"
#include"../header/SpecialEvent09.h"
#include"../header/SpecialEvent10.h"
#include"../header/SpecialEvent11.h"
#include"../header/SpecialEvent12.h"
#include"../header/SpecialEvent13.h"
#include"../header/SpecialEvent14.h"
#include"../header/SpecialEvent15.h"
#include"../header/SpecialEvent16.h"
#include"../header/SpecialEvent17.h"
#include"../header/SpecialEvent18.h"
#include"../header/SpecialEvent19.h"
#include"../header/SpecialEvent20.h"
#include"../header/SpecialEvent21.h"
#include"../header/SpecialEvent22.h"

Game::Game(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int loadDataNum) :saveDataList(saveDataList), loadDataNum(loadDataNum)
{
	state = GameState::MAP;
	stateEndFlag = false;
	playTime = 0;
	specialEventNum = loadDataNum != -1 ? -1 : 0;
	map = nullptr;
	playerData = new PlayerData(saveDataList,loadDataNum);
	specialEvent = nullptr;
}

Game::~Game()
{
	if (map != nullptr)
	{
		delete map;
	}

	delete playerData;

	if (specialEvent != nullptr)
	{
		delete specialEvent;
	}
}

void Game::Main()
{
	if (specialEventNum == -1)
	{
		MapFunc();
	}
	else
	{
		EventFunc();
	}
	playerData->Update();
}

void Game::UpdatePlayTime()
{
	playTime++;
}

void Game::MapFunc()
{
	if (map == nullptr)
	{
		map = new Map(playerData,saveDataList,loadDataNum);
	}

	map->Update();
	map->Draw();
	HappenEvent();
}

void Game::Save()
{

}

void Game::HappenEvent()
{
	if (map->GetSpecialEventNum() != -1 && map->GetEventInFlag())
	{
		specialEventNum = map->GetSpecialEventNum();
	}
}

void Game::EventFunc()
{
	switch (specialEventNum)
	{
	case 0:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent00();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 1:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent01();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 2:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent02();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 3:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent03();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 4:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent04();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 5:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent05();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 6:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent06();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 7:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent07();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 8:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent08();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 9:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent09();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 10:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent10();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 11:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent11();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 12:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent12();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 13:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent13();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 14:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent14();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 15:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent15();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 16:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent16();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 17:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent17();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 18:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent18();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 19:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent19();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 20:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent20();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 21:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent21();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	case 22:
		if (specialEvent == nullptr)
		{
			specialEvent = new SpecialEvent22();
		}

		specialEvent->Update();
		specialEvent->Draw();

		if (specialEvent->GetEndFlag())
		{
			delete specialEvent;
			specialEvent = nullptr;
		}
		break;
	default:
		assert(0 && "Game::EventFunc()");
		break;
	}
	if (specialEvent == nullptr)
	{
		if (map != nullptr)
		{
			map->ResetAfterEvent();
		}
		assert(specialEventNum < SpecialEventInfoList::GetSpecialEventInfoList().size() && "Game::EventFunt()");
		if (SpecialEventInfoList::GetSpecialEventInfoList()[specialEventNum].standFlag != -1)
		{
			playerData->StandFlag(SpecialEventInfoList::GetSpecialEventInfoList()[specialEventNum].standFlag);
		}
		for (auto& n : SpecialEventInfoList::GetSpecialEventInfoList()[specialEventNum].getItemList)
		{
			playerData->GetPlayerStatus()->AddItem(n);
		}
		for (auto& n : SpecialEventInfoList::GetSpecialEventInfoList()[specialEventNum].giveItemList)
		{
			playerData->GetPlayerStatus()->UseItem(n);
		}
		specialEventNum = -1;
	}
}

int Game::GetSaveDataNum()const
{
	if (map != nullptr)
	{
		return map->GetSaveDataNum();
	}

	return -1;
}

void Game::Save(int saveDataNum)
{
	map->Save(saveDataNum);
	playerData->Save(saveDataList, saveDataNum);
}

bool Game::GetStateEndFlag()const
{
	if (map != nullptr)
	{
		return map->GetEndFlag();
	}
	return false;
}