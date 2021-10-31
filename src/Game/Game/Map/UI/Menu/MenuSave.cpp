#include"../header/MenuSave.h"
#include"../header/KeyBoard.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"
#include"../header/MapInfoList.h"

GHandle MenuSave::conditionErrorGraph[(int)ConditionError::SIZE];

MenuSave::MenuSave(PlayerData* playerData, array<SaveData, Define::SAVE_DATA_NUM>& saveDataList,int& mapNum) :playerData(playerData),saveDataList(saveDataList),mapNum(mapNum)
{
	closeFlag = false;
	cursorNum1 = 0;
	cursorNum2 = 0;
	state = 0;
	saveDataNum = -1;
}

MenuSave::~MenuSave()
{

}

void MenuSave::Load()
{
	conditionErrorGraph[0] = LoadGraph("data/graph/ConditionError1.png");
	assert(conditionErrorGraph[0] != 0 && "MenuSave::Load()");
	conditionErrorGraph[1] = LoadGraph("data/graph/ConditionError2.png");
	assert(conditionErrorGraph[1] != 0 && "MenuSave::Load()");
	conditionErrorGraph[2] = LoadGraph("data/graph/ConditionError3.png");
	assert(conditionErrorGraph[2] != 0 && "MenuSave::Load()");
}

void MenuSave::Update()
{
	MoveCursor();
	Push();
}

void MenuSave::MoveCursor()
{
	switch (state)
	{
	case 0:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{

			cursorNum1--;
			cursorNum1 = max(0, cursorNum1);

		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{

			cursorNum1++;
			cursorNum1 = min(11, cursorNum1);
		}
		break;
	case 1:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{

			cursorNum2--;
			cursorNum2 = max(0, cursorNum2);

		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{

			cursorNum2++;
			cursorNum2 = min(1, cursorNum2);
		}
		break;
	}
}

void MenuSave::Push()
{
	switch (state)
	{
	case 0:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 1;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			closeFlag = true;
		}
		break;
	case 1:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			switch (cursorNum2)
			{
			case 0:
				Save();
				break;
			case 1:
				break;
			}
			state = 0;
			cursorNum2 = 0;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 0;
			cursorNum2 = 0;
		}
		break;
	}
}

void MenuSave::Save()
{
	saveDataNum = cursorNum1;
}

void MenuSave::Draw()
{
	Function::Alpha(100);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	DrawCharacterStatus();
	DrawTopic();

	if (state >= 0)
	{
		if (state == 1)
		{
			Function::Alpha(200);
		}

		DrawFillBox(130, 10, 300, 400, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(132, 12, 298, 398, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);



		static const int itemGapLengthY = 30;

		for (int i = 0; i < 12; i++)
		{
			if (cursorNum1 != i)
			{
				Function::Alpha(128);
			}

			DrawFormatStringToHandle(150, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "データ%d", i + 1);
			Function::Alpha(255);
		}

		Function::Alpha(255);
	}

	if (state == 1)
	{
		static const int itemGapLengthY = 30;

		DrawFillBox(680, 320, 770, 400, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(682, 322, 768, 398, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		for (int i = 0; i < 2; i++)
		{
			if (cursorNum2 != i)
			{
				Function::Alpha(128);
			}

			switch (i)
			{
			case 0:
				DrawFormatStringToHandle(700, 335 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "はい");
				break;
			case 1:
				DrawFormatStringToHandle(700, 335 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "いいえ");
				break;
			}
			Function::Alpha(255);
		}

		Function::Alpha(255);
	}

	DrawFillBox(130, 410, 770, 475, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
	DrawFillBox(132, 412, 768, 473, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

	switch (state)
	{
	case 0:
		if (saveDataList[cursorNum1].exist)
		{
			if (saveDataList[cursorNum1].existCharacterFlag[0])
			{
				DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "クリス Lv %d", saveDataList[cursorNum1].Lv[0]);
			}
			if (saveDataList[cursorNum1].existCharacterFlag[1])
			{
				DrawFormatStringToHandle(300, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "アリア Lv %d", saveDataList[cursorNum1].Lv[1]);
			}
			DrawFormatStringToHandle(145, 445, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "場所 %s", MapInfoList::GetMapInfoList()[saveDataList[cursorNum1].mapNum].name.c_str());

			int hour, minute, second;
			int time = saveDataList[cursorNum1].playTime;
			time /= 60;
			second = time % 60;
			time /= 60;
			minute = time % 60;
			time /= 60;
			hour = time % 60;

			int x = 700 - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[11], "プレイ時間 %02d:%02d:%02d", hour, minute, second);
			DrawFormatStringToHandle(x, 445, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "プレイ時間 %02d:%02d:%02d", hour, minute, second);
		}
		else
		{
			DrawFormatStringToHandle(400, 432, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "新規データ");
		}
		break;
	case 1:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "本当にセーブしてもよろしいですか？");
		break;
	}
}

void MenuSave::DrawTopic()
{
	Function::Alpha(200);
	DrawFillBox(10, 10, 120, 245, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
	DrawFillBox(12, 12, 118, 243, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
	Function::Alpha(255);

	static const string topicMessage[] = { "アイテム","スキル","装備","合成","実績","セーブ","タイトル" };
	static const int gapLength = 30;
	for (int i = 0; i < 7; i++)
	{
		Function::Alpha(128);
		DrawFormatStringToHandle(Function::CalcCenterOfString(10, 120, FontMgr::GetFont()[11], topicMessage[i].c_str()), 30 + gapLength*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], topicMessage[i].c_str());
		Function::Alpha(255);
	}
}

void MenuSave::DrawCharacterStatus()
{
	static int gapLength = 190;
	int digits1, digits2;
	for (int i = 0; i != playerData->GetCharacterStatusList().size(); i++)
	{
		if (!playerData->GetExistCharacterFlag()[i])
		{
			continue;
		}
		Function::Alpha(128);
		DrawFillBox(10 + gapLength*i, 500, 190 + gapLength*i, 590, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);

		DrawFormatStringToHandle(20 + gapLength*i, 505, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[10], playerData->GetCharacterStatusList()[i]->GetName().c_str());
		DrawFormatStringToHandle(75 + gapLength*i, 505, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[10], "Lv %d", playerData->GetCharacterStatusList()[i]->GetLv());

		DrawFormatStringToHandle(23 + gapLength*i, 525, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[10], "HP:");
		DrawFillBox(60 + gapLength*i, 532, 180 + gapLength*i, 540, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		DrawFillBox(57 + gapLength*i, 529, (int)(57 + 120 * ((double)playerData->GetCharacterStatusList()[i]->GetHP() / playerData->GetCharacterStatusList()[i]->GetMAX_HP())) + gapLength*i, 537, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::GREEN]);

		if (playerData->GetCharacterStatusList()[i]->GetHP() > 0)
		{
			digits1 = (int)log10(playerData->GetCharacterStatusList()[i]->GetHP());
		}
		else
		{
			digits1 = 0;
		}
		digits2 = (int)log10(playerData->GetCharacterStatusList()[i]->GetMAX_HP());
		DrawFormatStringToHandle(165 - 7 * digits2 - 10 - 10 - 7 * digits1 + gapLength * i, 525, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "%d", playerData->GetCharacterStatusList()[i]->GetHP());
		DrawFormatStringToHandle(165 - 7 * digits2 - 10 + gapLength * i, 525, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "/");
		DrawFormatStringToHandle(165 - 7 * digits2 + gapLength * i, 525, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[9], "%d", playerData->GetCharacterStatusList()[i]->GetMAX_HP());

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
				DrawRotaGraph(130 + gapX*j + gapLength*i, 513, 0.5, 0.0, conditionErrorGraph[j], TRUE);
			}
		}
	}
}
