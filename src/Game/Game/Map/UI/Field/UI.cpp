#include"../header/UI.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"
#include"../header/KeyBoard.h"
#include"../header/CharacterSkillInfoList.h"
#include"../header/CharacterStatus.h"

GHandle UI::keyGraph[4];
GHandle UI::conditionErrorGraph[(int)ConditionError::SIZE];

UI::UI(PlayerMap* playerMap, PlayerData* playerData, list<EnemyMapPtr>& enemyMapList, list<BossMapPtr>& bossMapList, list<ObjectMapPtr>& objectMapList, list<PeopleMapPtr>& peopleMapList, list<DropItemPtr>& dropItemMapList, SystemMessage* systemMessage, int& mapNum) :enemyMapList(enemyMapList),mapNum(mapNum),playerMap(playerMap),playerData(playerData), systemMessage(systemMessage),bossMapList(bossMapList),objectMapList(objectMapList),dropItemMapList(dropItemMapList),peopleMapList(peopleMapList)
{
	mapUI = new MapUI(playerMap, enemyMapList,bossMapList,objectMapList,peopleMapList,dropItemMapList, mapNum);
	showFlag = true;
}

UI::~UI()
{
	delete mapUI;
}

void UI::Load()
{
	keyGraph[0] = LoadGraph("data/graph/w.png");
	assert(keyGraph[0] != 0 && "UI::Load()");
	keyGraph[1] = LoadGraph("data/graph/a.png");
	assert(keyGraph[1] != 0 && "UI::Load()");
	keyGraph[2] = LoadGraph("data/graph/s.png");
	assert(keyGraph[2] != 0 && "UI::Load()");
	keyGraph[3] = LoadGraph("data/graph/d.png");
	assert(keyGraph[3] != 0 && "UI::Load()");
	conditionErrorGraph[0] = LoadGraph("data/graph/ConditionError1.png");
	assert(conditionErrorGraph[0] != 0 && "UI::Load()");
	conditionErrorGraph[1] = LoadGraph("data/graph/ConditionError2.png");
	assert(conditionErrorGraph[1] != 0 && "UI::Load()");
	conditionErrorGraph[2] = LoadGraph("data/graph/ConditionError3.png");
	assert(conditionErrorGraph[2] != 0 && "UI::Load()");
}

void UI::Update()
{
	if (showFlag)
	{
		systemMessage->Update();
	}
	PushQ();
}

void UI::PushQ()
{
	if (KeyBoard::PushOnce(KEY_INPUT_Q))
	{
		showFlag = !showFlag;
	}
}

void UI::Draw()
{
	if (!showFlag)
	{
		return;
	}
	systemMessage->Draw();
	mapUI->Draw();
	DrawCharacterStatus();
	DrawOperation();
}

void UI::DrawOperation()
{
	Function::Alpha(128);
	DrawFillBox(400, 560, 523, 590, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	DrawFillBox(533, 560, 656, 590, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	DrawFillBox(666, 560, 789, 590, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	DrawFillBox(533, 520, 656, 550, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	DrawRotaGraph(415, 575, 0.8, 0.0, keyGraph[1], TRUE);
	DrawRotaGraph(548, 575, 0.8, 0.0, keyGraph[2], TRUE);
	DrawRotaGraph(681, 575, 0.8, 0.0, keyGraph[3], TRUE);
	DrawRotaGraph(548, 535, 0.8, 0.0, keyGraph[0], TRUE);

	if (playerData->GetCharacterStatusList()[playerMap->GetID()]->GetSetSkill()[0] != -1)
	{
		DrawFormatStringToHandle(Function::CalcCenterOfString(420, 523, FontMgr::GetFont()[9], CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[playerMap->GetID()]->GetSetSkill()[0]].name.c_str()), 568, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[playerMap->GetID()]->GetSetSkill()[0]].name.c_str());
	}	
	if (playerData->GetCharacterStatusList()[playerMap->GetID()]->GetSetSkill()[1] != -1)
	{
		DrawFormatStringToHandle(Function::CalcCenterOfString(553, 656, FontMgr::GetFont()[9], CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[playerMap->GetID()]->GetSetSkill()[1]].name.c_str()), 568, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[playerMap->GetID()]->GetSetSkill()[1]].name.c_str());
	}
	if (playerData->GetCharacterStatusList()[playerMap->GetID()]->GetSetSkill()[2] != -1)
	{
		DrawFormatStringToHandle(Function::CalcCenterOfString(686, 789, FontMgr::GetFont()[9], CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[playerMap->GetID()]->GetSetSkill()[2]].name.c_str()), 568, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[playerMap->GetID()]->GetSetSkill()[2]].name.c_str());
	}
	DrawFormatStringToHandle(Function::CalcCenterOfString(553, 656, FontMgr::GetFont()[9], "’ÊíUŒ‚"), 528, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "’ÊíUŒ‚");
}

void UI::DrawCharacterStatus()
{
	static int gapLength = 190;
	int digits1, digits2;
	for (int i = 0; i != playerData->GetCharacterStatusList().size(); i++)
	{
		if (!playerData->GetExistCharacterFlag()[i])
		{
			continue;
		}
		if (i == playerMap->GetID())
		{
			Function::Alpha(128);
			DrawFillBox(8 + gapLength*i, 498, 192 + gapLength*i, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
			Function::Alpha(255);
		}
		Function::Alpha(128);
		DrawFillBox(10 + gapLength*i, 500, 190 + gapLength*i, 590, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);

		DrawFormatStringToHandle(20 + gapLength*i, 505, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[10], playerData->GetCharacterStatusList()[i]->GetName().c_str());
		DrawFormatStringToHandle(75 + gapLength*i, 505, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[10], "Lv %d", playerData->GetCharacterStatusList()[i]->GetLv());

		DrawFormatStringToHandle(23 + gapLength*i, 525, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[10], "HP:");
		DrawFillBox(60 + gapLength*i, 532, 180 + gapLength*i, 540, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		DrawFillBox(57 + gapLength*i, 529, (int)(57+120*((double)playerData->GetCharacterStatusList()[i]->GetHP()/ playerData->GetCharacterStatusList()[i]->GetMAX_HP())) + gapLength*i, 537, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::GREEN]);

		if (playerData->GetCharacterStatusList()[i]->GetHP() > 0)
		{
			digits1 = (int)log10(playerData->GetCharacterStatusList()[i]->GetHP());
		}
		else
		{
			digits1 = 0;
		}
		digits2 = (int)log10(playerData->GetCharacterStatusList()[i]->GetMAX_HP());
		DrawFormatStringToHandle(165 - 7 * digits2 - 10 - 10 - 7 * digits1+gapLength * i, 525, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "%d", playerData->GetCharacterStatusList()[i]->GetHP());
		DrawFormatStringToHandle(165 - 7 * digits2 - 10+ gapLength * i, 525, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "/");
		DrawFormatStringToHandle(165 - 7 * digits2+ gapLength * i, 525, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "%d", playerData->GetCharacterStatusList()[i]->GetMAX_HP());

		DrawFormatStringToHandle(23 + gapLength*i, 545, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[10], "SP:");
		DrawFillBox(60 + gapLength*i, 552, 180 + gapLength*i, 560, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		DrawFillBox(57 + gapLength*i, 549, (int)(57 + 120 * ((double)playerData->GetCharacterStatusList()[i]->GetSP() / playerData->GetCharacterStatusList()[i]->GetMAX_SP())) + gapLength*i, 557, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLUE]);

		if (playerData->GetCharacterStatusList()[i]->GetSP() > 0)
		{
			digits1 = (int)log10(playerData->GetCharacterStatusList()[i]->GetSP());
		}
		else
		{
			digits1 = 0;
		}
		digits2 = (int)log10(playerData->GetCharacterStatusList()[i]->GetMAX_SP());
		DrawFormatStringToHandle(165 - 7 * digits2 - 10 - 10 - 7 * digits1 + gapLength * i, 545, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "%d", playerData->GetCharacterStatusList()[i]->GetSP());
		DrawFormatStringToHandle(165 - 7 * digits2 - 10 + gapLength * i, 545, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "/");
		DrawFormatStringToHandle(165 - 7 * digits2 + gapLength * i, 545, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "%d", playerData->GetCharacterStatusList()[i]->GetMAX_SP());

		DrawFormatStringToHandle(23 + gapLength*i, 565, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[10], "EX:");
		DrawFillBox(60 + gapLength*i, 572, 180 + gapLength*i, 580, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		DrawFillBox(57 + gapLength*i, 569, (int)(57 + 120 * ((double)playerData->GetCharacterStatusList()[i]->GetEXP() / CharacterStatus::NeedEXP[i][playerData->GetCharacterStatusList()[i]->GetLv()])) + gapLength*i, 577, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::LIGHTBLUE]);

		if (playerData->GetCharacterStatusList()[i]->GetEXP() > 0)
		{
			digits1 = (int)log10(playerData->GetCharacterStatusList()[i]->GetEXP());
		}
		else
		{
			digits1 = 0;
		}
		digits2 = (int)log10(CharacterStatus::NeedEXP[i][playerData->GetCharacterStatusList()[i]->GetLv()]);
		DrawFormatStringToHandle(165 - 7 * digits2 - 10 - 10 - 7 * digits1 + gapLength * i, 565, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "%d", playerData->GetCharacterStatusList()[i]->GetEXP());
		DrawFormatStringToHandle(165 - 7 * digits2 - 10 + gapLength * i, 565, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "/");
		DrawFormatStringToHandle(165 - 7 * digits2 + gapLength * i, 565, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "%d", CharacterStatus::NeedEXP[i][playerData->GetCharacterStatusList()[i]->GetLv()]);

		static const int gapX = 20;
		static const int flashTime = 180;
		for (int j = 0; j < (int)ConditionError::SIZE; j++)
		{
			if (playerData->GetCharacterStatusList()[i]->GetConditionError()[j])
			{
				if (playerData->GetCharacterStatusList()[i]->GetConditionErrorTimer()[j] < flashTime && playerData->GetCharacterStatusList()[i]->GetConditionErrorTimer()[j] % 10 < 5)
				{

				}
				else
				{
					DrawRotaGraph(130 + gapX*j + gapLength*i, 513, 0.5, 0.0, conditionErrorGraph[j], TRUE);
				}
			}
		}
	}
}

void UI::ChangeMap()
{
	mapUI->Cash();
}