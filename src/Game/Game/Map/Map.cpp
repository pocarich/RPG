#include"../header/Map.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"
#include"../header/ItemInfoList.h"
#include"../header/MapChangeInfoList.h"
#include"../header/MapInfoList.h"
#include"../header/PeopleInfoList.h"
#include"../header/EventInfoList.h"
#include"../header/CharacterSkillInfoList.h"
#include"../header/SpecialEventInfoList.h"

#include"../header/KeyBoard.h"

#include"../header/ObjectMap000.h"
#include"../header/ObjectMap001.h"

Map::Map(PlayerData* playerData, array<SaveData, Define::SAVE_DATA_NUM>& saveDataList, int loadDataNum):playerData(playerData),mapNum(95),saveDataList(saveDataList)
{
	if (loadDataNum != -1)
	{
		mapNum = saveDataList[loadDataNum].mapNum;
	}

	systemMessage = new SystemMessage();
	playerMap = new PlayerMap(playerData,systemMessage,bossMapList,objectMapList,enemyMapList, peopleMapList, camera, battleEffectList,dropItemList,textUIList ,mapNum, saveDataList, loadDataNum);
	monsterSpawner = new MonsterSpawner(playerData,playerMap,bossMapList,objectMapList,enemyMapList, peopleMapList,textUIList,dropItemList,mapNum, camera, battleEffectList);
	ui = new UI(playerMap,playerData, enemyMapList,bossMapList,objectMapList,peopleMapList,dropItemList,systemMessage,mapNum);
	mapField = new MapField(playerMap,mapNum,camera);
	camera = playerMap->GetPosition() - Vector2<double>(Define::WINDOW_WIDTH / 2.0, Define::WINDOW_HEIGHT / 2.0);
	mapState = MapState::NON;
	darkAlpha = 0;
	eventInFlag = false;
	gameOverTimer = 0;
	gameOverFlag = false;
	eventInTimer = 0;
	areaChangeFlag = false;
	areaChangeTimer = 0;
	specialEventNum = -1;
	menu = nullptr;
	talkMgr = nullptr;
	eventMgr = nullptr;
	shop = nullptr;
	_INN = nullptr;

	UpdateMapInfo();
	PeopleSpawn();
	ObjectSpawn();
	monsterSpawner->FirstSpawn();

	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		nowLv[i] = playerData->GetCharacterStatusList()[i]->GetLv();
	}
}

Map::~Map()
{
	if (playerMap != nullptr)
	{
		delete playerMap;
	}
	if (mapField != nullptr)
	{
		delete mapField;
	}
	if (menu != nullptr)
	{
		delete menu;
	}
	if (eventMgr != nullptr)
	{
		delete eventMgr;
	}
	if (talkMgr != nullptr)
	{
		delete talkMgr;
	}
	if (shop != nullptr)
	{
		delete shop;
	}
	if (_INN != nullptr)
	{
		delete _INN;
	}
}

void Map::UpdateMapInfo()
{
	for (int i = 0; i != MapChangeInfoList::GetMapChangeInfoList().size(); i++)
	{
		MapChangeInfo info = MapChangeInfoList::GetMapChangeInfoList()[i];
		if (mapNum == info.mapNum)
		{
			if ((info.disappearFlag == -1 || !playerData->GetFlagList()[info.disappearFlag]) && (info.appearFlag == -1 || playerData->GetFlagList()[info.appearFlag]))
			{
				MapInfoList::GetMapInfoList()[mapNum].areaChange[info.y][info.x] = i;
			}
		}
	}

	for (int i = 0; i != EventInfoList::GetEventInfoList().size(); i++)
	{
		EventInfo info = EventInfoList::GetEventInfoList()[i];
		if (mapNum == info.mapNum)
		{
			if ((info.disappearFlag == -1 || !playerData->GetFlagList()[info.disappearFlag]) && (info.appearFlag == -1 || playerData->GetFlagList()[info.appearFlag]))
			{
				MapInfoList::GetMapInfoList()[mapNum].event[info.y][info.x] = i;
			}
		}
	}
}

void Map::Update()
{
	switch (mapState)
	{
	case MapState::NON:
		if (specialEventNum == -1)
		{
			monsterSpawner->Update();
			playerMap->Update();
			for (auto& obj : playerData->GetCharacterStatusList())
			{
				obj->UpdateMap();
			}
			for (auto& obj : enemyMapList)
			{
				obj->Update();
			}
			for (auto& obj : bossMapList)
			{
				obj->Update();
			}
			for (auto& obj : peopleMapList)
			{
				obj->Update();
			}
			for (auto& obj : textUIList)
			{
				obj->Update();
			}
			for (auto& obj : dropItemList)
			{
				obj->Update();
			}
			for (auto& obj : objectMapList)
			{
				obj->Update();
			}
			if (playerMap->GetMapChangeFlag())
			{
				mapState = MapState::AREACHANGE;
			}
			TalkIn();
			CheckCharacterLv();
			EventIn();
			OpenMenu();

			if (playerMap->GetDeathFlag())
			{
				UpdateGameOver();
			}
			for (auto& obj : battleEffectList)
			{
				obj->Update();
			}
		}
		else
		{
			UpdateEventIn();
		}
		break;
	case MapState::AREACHANGE:
		UpdateAreaChange();
		break;
	case MapState::MENU:
		menu->Update();
		CloseMenu();
		break;
	case MapState::TALK:
		//UpdateWindowList();
		if (windowList.size() != 0)
		{
			windowList.back()->Update();
		}
		//else
		{
			talkMgr->Update();
		}
		TalkEnd();
		break;
	case MapState::EVENT:
		//UpdateWindowList();
		if (windowList.size() != 0)
		{
			windowList.back()->Update();
		}
		//	else
		{
			eventMgr->Update();
		}
		EventEnd();
		break;
	case MapState::SHOP:
		shop->Update();
		ShopEnd();
		break;
	case MapState::INN:
		_INN->Update();
		INNEnd();
		break;
	}
	mapField->Update();
	ui->Update();

	DeleteBattleEffect();
	DeleteEnemy();
	DeleteTextUI();
	DeleteObject();
	UpdateCamera();
	DeleteDropItem();
	DeleteBoss();
	PushE();
}

void Map::UpdateGameOver()
{
	if (KeyBoard::PushOnce(KEY_INPUT_Z))
	{
		gameOverFlag = true;
	}
	if (gameOverFlag)
	{
		darkAlpha += 3;
		darkAlpha = min(darkAlpha, 255);
		gameOverTimer++;
		gameOverTimer = min(gameOverTimer, gameOverDelay);
	}
}

void Map::UpdateEventIn()
{
	eventInTimer++;
	darkAlpha += 5;
	darkAlpha = min(255, darkAlpha);
	if (eventInTimer == Define::EVENT_IN_TIME)
	{
		eventInFlag = true;
		playerMap->ResetSpecialEvent();
		playerMap->ResetEvent();
	}
}

void Map::CheckCharacterLv()
{
	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		if (nowLv[i] != playerData->GetCharacterStatusList()[i]->GetLv())
		{
			stringstream ss;
			ss << playerData->GetCharacterStatusList()[i]->GetName() << "‚ÍƒŒƒxƒ‹‚ª" << playerData->GetCharacterStatusList()[i]->GetLv() << "‚Éã‚ª‚Á‚½B";
			systemMessage->AddMessage(ss.str());
			for (int j = nowLv[i] + 1; j < playerData->GetCharacterStatusList()[i]->GetLv() + 1; j++)
			{
				for (auto& n : CharacterStatus::LearnSkill[i][j])
				{
					if (n != -1)
					{
						stringstream ss2;
						ss2 << playerData->GetCharacterStatusList()[i]->GetName() << "‚Í" << CharacterSkillInfoList::GetCharacterSkillInfoList()[n].name << "‚ðK“¾‚µ‚½B";
						systemMessage->AddMessage(ss2.str());
					}
				}
			}
			nowLv[i] = playerData->GetCharacterStatusList()[i]->GetLv();
		}
	}
}

void Map::ShopEnd()
{
	if (shop->GetCloseFlag())
	{
		delete shop;
		shop = nullptr;
		mapState = MapState::NON;
	}
}

void Map::INNEnd()
{
	if (_INN->GetCloseFlag())
	{
		delete _INN;
		_INN = nullptr;
		mapState = MapState::NON;
	}
}

void Map::UpdateWindowList()
{
	auto itr = remove_if(windowList.begin(), windowList.end(), [](WindowPtr& obj)
	{
		return obj->GetEndFlag();
	});
	windowList.erase(itr, windowList.end());
}

void Map::TalkIn()
{
	if (playerMap->GetPeopleNum() != -1)
	{
		if (PeopleInfoList::GetPeopleInfoList()[playerMap->GetPeopleNum()].standFlag != -1)
		{
			playerData->StandFlag(PeopleInfoList::GetPeopleInfoList()[playerMap->GetPeopleNum()].standFlag);
		}
		for (auto& n : PeopleInfoList::GetPeopleInfoList()[playerMap->GetPeopleNum()].getItems)
		{
			playerData->GetPlayerStatus()->AddItem(n);
		}
		for (auto& n : PeopleInfoList::GetPeopleInfoList()[playerMap->GetPeopleNum()].giveItems)
		{
			playerData->GetPlayerStatus()->UseItem(n);
		}
		if (PeopleInfoList::GetPeopleInfoList()[playerMap->GetPeopleNum()].specialEvent == -1)
		{
			mapState = MapState::TALK;
			talkMgr = new TalkMgr(playerMap->GetPeopleNum(), windowList);
		}
		else
		{
			specialEventNum = PeopleInfoList::GetPeopleInfoList()[playerMap->GetPeopleNum()].specialEvent;
		}
	}
}

void Map::TalkEnd()
{
	if (talkMgr->GetEndFlag() && windowList.size() == 0)
	{
		mapState = MapState::NON;
		delete talkMgr;
		talkMgr = nullptr;
		playerMap->ResetEvent();
	}
}

void Map::EventIn()
{
	if (playerMap->GetEventNum() != -1)
	{
		assert(playerMap->GetEventNum() < EventInfoList::GetEventInfoList().size() && "Map::EventIn()");
		if (EventInfoList::GetEventInfoList()[playerMap->GetEventNum()].standFlag != -1)
		{
			playerData->StandFlag(EventInfoList::GetEventInfoList()[playerMap->GetEventNum()].standFlag);
		}
		for (auto& n : EventInfoList::GetEventInfoList()[playerMap->GetEventNum()].getItems)
		{
			playerData->GetPlayerStatus()->AddItem(n);
			playerData->GetRecipe(n);
		}
		for (auto& n : EventInfoList::GetEventInfoList()[playerMap->GetEventNum()].giveItems)
		{
			playerData->GetPlayerStatus()->UseItem(n);
		}

		int tempSpecialEventNum = EventInfoList::GetEventInfoList()[playerMap->GetEventNum()].specialEventNum;
		if (tempSpecialEventNum == -1)
		{
			mapState = MapState::EVENT;
			eventMgr = new EventMgr(playerMap->GetEventNum(), windowList);
		}
		if (Define::EVENT_SHOP_START <= tempSpecialEventNum&& tempSpecialEventNum <= Define::EVENT_SHOP_END)
		{
			mapState = MapState::SHOP;
			shop = new Shop(playerData, tempSpecialEventNum);
		}
		else if (Define::EVENT_INN_START <= tempSpecialEventNum&& tempSpecialEventNum <= Define::EVENT_INN_END)
		{
			mapState = MapState::INN;
			_INN = new INN(playerData, tempSpecialEventNum);
		}
		else
		{
			specialEventNum = tempSpecialEventNum;
		}
		if (specialEventNum == -1)
		{
			playerMap->ResetEvent();
		}
	}
	else if (playerMap->GetSpecialEventNum() != -1)
	{
		specialEventNum = playerMap->GetSpecialEventNum();
	}
}

void Map::EventEnd()
{
	if (eventMgr->GetEndFlag() && windowList.size() == 0)
	{
		mapState = MapState::NON;
		delete eventMgr;
		eventMgr = nullptr;
	}
}

void Map::OpenMenu()
{
	if (playerMap->GetDeathFlag() || playerData->GetCharacterStatusList()[playerMap->GetID()]->GetConditionError()[(int)ConditionError::SLEEP])
	{
		return;
	}

	if (KeyBoard::PushOnce(KEY_INPUT_C))
	{
		mapState = MapState::MENU;
		menu = new Menu(playerData, saveDataList, mapNum, find_if(objectMapList.begin(), objectMapList.end(), [&](ObjectMapPtr& obj) {return obj->GetKind() == 8 && obj->GetMasuPosition() == playerMap->GetMasuPosition(); }) != objectMapList.end());
	}
}

void Map::CloseMenu()
{
	if (menu->GetCloseFlag())
	{
		mapState = MapState::NON;
		delete menu;
		menu = nullptr;
	}
}

void Map::PushE()
{
	
}

void Map::DeleteBattleEffect()
{
	battleEffectList.erase(remove_if(battleEffectList.begin(), battleEffectList.end(), [&](BattleEffectPtr& obj) {return obj->GetDisappearFlag(); }), battleEffectList.end());
}

void Map::DeleteTextUI()
{
	textUIList.erase(remove_if(textUIList.begin(), textUIList.end(), [&](TextUIPtr& obj) {return obj->GetDeleteFlag(); }), textUIList.end());
}

void Map::DeleteObject()
{
	for (auto& obj : objectMapList)
	{
		if (obj->GetDeathFlag())
		{
			obj->Death();
		}
	}
	objectMapList.erase(remove_if(objectMapList.begin(), objectMapList.end(), [&](ObjectMapPtr& obj) {return obj->GetDeathFlag(); }), objectMapList.end());
}

void Map::DeleteEnemy()
{
	for (auto& obj : enemyMapList)
	{
		if (obj->GetDeathFlag())
		{
			obj->Death();
		}
	}
	enemyMapList.erase(remove_if(enemyMapList.begin(), enemyMapList.end(), [&](EnemyMapPtr& obj) {return obj->GetDeathFlag(); }), enemyMapList.end());
}

void Map::DeleteBoss()
{
	for (auto& obj : bossMapList)
	{
		if (obj->GetDeathFlag())
		{
			obj->Death();
			if (count_if(bossMapList.begin(), bossMapList.end(), [&](BossMapPtr& obj) {return !obj->GetDeathFlag(); }) == 0)
			{
				MapInfoList::GetMapInfoList()[mapNum].Reset();
				UpdateMapInfo();
			}
		}
	}
	bossMapList.erase(remove_if(bossMapList.begin(), bossMapList.end(), [&](BossMapPtr& obj) {return obj->GetDeathFlag(); }), bossMapList.end());
}

void Map::DeleteDropItem()
{
	dropItemList.erase(remove_if(dropItemList.begin(), dropItemList.end(), [&](DropItemPtr& obj) {return obj->GetDeleteFlag(); }), dropItemList.end());
}

void Map::UpdateCamera()
{
	camera = playerMap->GetPosition() - Vector2<double>(Define::WINDOW_WIDTH / 2.0, Define::WINDOW_HEIGHT / 2.0);
}

void Map::UpdateAreaChange()
{
	areaChangeTimer++;

	if (areaChangeTimer < 50)
	{
		darkAlpha += 6;
		darkAlpha = min(255, darkAlpha);
	}
	else
	{
		darkAlpha -= 6;
		darkAlpha = max(0, darkAlpha);
	}

	if (areaChangeTimer == 50)
	{
		int tempMapNum = mapNum;
		playerMap->MapChange();
		playerMap->ResetMapChangeFlag();
		enemyMapList.clear();
		monsterSpawner->Reset();
		objectMapList.clear();
		dropItemList.clear();
		battleEffectList.clear();
		ChangeMap();
		MapInfoList::GetMapInfoList()[tempMapNum].Reset();
		UpdateMapInfo();
		PeopleSpawn();
		ObjectSpawn();
		ui->ChangeMap();
		monsterSpawner->FirstSpawn();
	}
	if (areaChangeTimer == 100)
	{
		mapState = MapState::NON;
		areaChangeTimer = 0;
		areaChangeFlag = false;
	}
}

void Map::ChangeMap()
{
	peopleMapList.clear();
}

void Map::PeopleSpawn()
{
	for (int i = 0; i != PeopleInfoList::GetPeopleInfoList().size();i++)
	{
		PeopleInfo info = PeopleInfoList::GetPeopleInfoList()[i];
		if (info.mapNum == mapNum)
		{
			if ((info.disappearFlag == -1 || !playerData->GetFlagList()[info.disappearFlag]) && (info.appearFlag == -1 || playerData->GetFlagList()[info.appearFlag]))
			{
				peopleMapList.push_back(make_shared<PeopleMap>(i, playerMap, bossMapList, objectMapList, enemyMapList, camera, mapNum));
			}
		}
	}
}

void Map::ObjectSpawn()
{
	for (int i = 0; i != MapInfoList::GetMapInfoList()[mapNum].popObjectKindList.size(); i++)
	{
		if ((MapInfoList::GetMapInfoList()[mapNum].objectNotPopFlag[i] == -1 || !playerData->GetFlagList()[MapInfoList::GetMapInfoList()[mapNum].objectNotPopFlag[i]]) && (MapInfoList::GetMapInfoList()[mapNum].objectPopFlag[i] == -1 || playerData->GetFlagList()[MapInfoList::GetMapInfoList()[mapNum].objectPopFlag[i]]))
		{
			switch (MapInfoList::GetMapInfoList()[mapNum].popObjectKindList[i])
			{
			default:
				objectMapList.push_back(make_shared<ObjectMap>(MapInfoList::GetMapInfoList()[mapNum].popObjectKindList[i],MapInfoList::GetMapInfoList()[mapNum].popObjectPositionList[i], playerData, playerMap, textUIList, battleEffectList, bossMapList, objectMapList, peopleMapList, enemyMapList, dropItemList, mapNum, camera));
				break;
			}
		}
	}
}

void Map::Draw()
{
	mapField->Draw();
	for (auto& obj : enemyMapList)
	{
		obj->DrawAttackPoint();
	}
	for (auto& obj : bossMapList)
	{
		obj->DrawAttackPoint();
	}
	for (auto& obj : objectMapList)
	{
		obj->Draw();
	}
	for (auto& obj : dropItemList)
	{
		obj->Draw();
	}
	for (auto& obj : enemyMapList)
	{
		obj->Draw();
	}
	for (auto& obj : bossMapList)
	{
		obj->Draw();
	}
	for (auto& obj : peopleMapList)
	{
		obj->Draw();
	}
	playerMap->Draw();
	for (auto& obj : battleEffectList)
	{
		obj->Draw();
	}
	for (auto& obj : enemyMapList)
	{
		obj->DrawHP();
	}
	for (auto& obj : bossMapList)
	{
		obj->DrawHP();
	}
	for (auto& obj : textUIList)
	{
		obj->Draw();
	}

	switch (mapState)
	{
	case MapState::NON:
		ui->Draw();
		break;
	case MapState::AREACHANGE:
		ui->Draw();
		break;
	case MapState::MENU:
		menu->Draw();
		break;
	case MapState::TALK:
		if (windowList.size() != 0)
		{
			windowList.back()->Draw();
		}
		break;
	case MapState::EVENT:
		if (windowList.size() != 0)
		{
			windowList.back()->Draw();
		}
		break;
	case MapState::SHOP:
		shop->Draw();
		break;
	case MapState::INN:
		_INN->Draw();
		break;
	}

	if (playerMap->GetDeathFlag())
	{
		DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[14], "GAME OVER"), 270, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[14], "GAME OVER");
	}

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);
}

void Map::ResetAfterEvent()
{
	if (specialEventNum == -1)
	{
		return;
	}
	int tempNum = mapNum;
	mapNum = SpecialEventInfoList::GetSpecialEventInfoList()[specialEventNum].mapNum;
	enemyMapList.clear();
	monsterSpawner->Reset();
	objectMapList.clear();
	dropItemList.clear();
	battleEffectList.clear();
	ChangeMap();
	MapInfoList::GetMapInfoList()[tempNum].Reset();
	UpdateMapInfo();
	PeopleSpawn();
	ObjectSpawn();
	ui->ChangeMap();
	monsterSpawner->FirstSpawn();

	specialEventNum = -1;
	darkAlpha = 0;
	eventInFlag = false;
	eventInTimer = 0;
}

int Map::GetSaveDataNum()const 
{
	if (menu != nullptr)
	{
		return menu->GetSaveDataNum();
	}
	return -1;
}

void Map::Save(int saveDataNum)
{
	playerMap->Save(saveDataList, saveDataNum);
	saveDataList[saveDataNum].mapNum = mapNum;
}

bool Map::GetEndFlag()const 
{
	if (gameOverTimer == gameOverDelay)
	{
		return true;
	}
	if (menu != nullptr)
	{
		return menu->GetEndFlag();
	}
	return false;
}