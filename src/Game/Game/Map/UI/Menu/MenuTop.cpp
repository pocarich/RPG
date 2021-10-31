#include"../header/MenuTop.h"
#include"../header/KeyBoard.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"

GHandle MenuTop::conditionErrorGraph[(int)ConditionError::SIZE];

MenuTop::MenuTop(PlayerData* playerData, bool canSave) :playerData(playerData), canSave(canSave)
{
	closeFlag = false;
	pushFlag = false;
	topic = Topic::ITEM;
}

MenuTop::~MenuTop()
{

}

void MenuTop::Load()
{
	conditionErrorGraph[0] = LoadGraph("data/graph/ConditionError1.png");
	assert(conditionErrorGraph[0] != 0 && "MenuTop::Load()");
	conditionErrorGraph[1] = LoadGraph("data/graph/ConditionError2.png");
	assert(conditionErrorGraph[1] != 0 && "MenuTop::Load()");
	conditionErrorGraph[2] = LoadGraph("data/graph/ConditionError3.png");
	assert(conditionErrorGraph[2] != 0 && "MenuTop::Load()");
}

void MenuTop::Update()
{
	MoveCursor();
	Push();
}

void MenuTop::MoveCursor()
{
	if (KeyBoard::PushOnce(KEY_INPUT_UP))
	{
		int n = (int)topic;
		n--;
		if (!canSave)
		{
			if ((Topic)n == Topic::SAVE)
			{
				n--;
			}
		}
		n = max(0, n);
		topic = (Topic)n;
	}
	if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
	{
		int n = (int)topic;
		n++;

		if (!canSave)
		{
			if ((Topic)n == Topic::SAVE)
			{
				n++;
			}
		}
		n = min((int)Topic::SIZE - 1, n);

		topic = (Topic)n;
	}
}

void MenuTop::Push()
{
	if (KeyBoard::PushOnce(KEY_INPUT_Z))
	{
		pushFlag = true;
	}

	if (KeyBoard::PushOnce(KEY_INPUT_X))
	{
		closeFlag = true;
	}
}

void MenuTop::Draw()
{
	Function::Alpha(100);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	DrawCharacterStatus();
	DrawHoldMoney();
	DrawPlayTime();

	DrawFillBox(10, 10, 120, 245, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
	DrawFillBox(12, 12, 118, 243, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

	static const string topicMessage[] = { "アイテム","スキル","装備","合成","実績","セーブ","タイトル" };
	static const int gapLength = 30;
	for (int i = 0; i < 7; i++)
	{
		if ((int)topic != i)
		{
			Function::Alpha(128);
			DrawFormatStringToHandle(Function::CalcCenterOfString(10, 120, FontMgr::GetFont()[11], topicMessage[i].c_str()), 30 + gapLength*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], topicMessage[i].c_str());
			Function::Alpha(255);
		}
		else
		{
			DrawFormatStringToHandle(Function::CalcCenterOfString(10, 120, FontMgr::GetFont()[11], topicMessage[i].c_str()), 30 + gapLength*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], topicMessage[i].c_str());
		}
	}
}

void MenuTop::DrawPlayTime()
{
	DrawFillBox(598, 498, 792, 542, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
	DrawFillBox(600, 500, 790, 540, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

	int hour, minute, second;
	int time = playerData->GetPlayTime();
	time /= 60;
	second = time % 60;
	time /= 60;
	minute = time % 60;
	time /= 60;
	hour = time % 60;

	int x = 780 - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[11], "%02d:%02d:%02d", hour, minute, second);
	DrawFormatStringToHandle(x, 510, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%02d:%02d:%02d", hour, minute, second);
	DrawFormatStringToHandle(610, 510, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "タイム：");
}

void MenuTop::DrawHoldMoney()
{
	DrawFillBox(598, 548, 792, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
	DrawFillBox(600, 550, 790, 590, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

	int digits1;
	if (playerData->GetPlayerStatus()->GetMoney() == 0)
	{
		digits1 = 0;
	}
	else
	{
		digits1 = (int)log10(playerData->GetPlayerStatus()->GetMoney());
	}

	DrawFormatStringToHandle(770 - 10 * digits1 - 18, 560, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
	DrawFormatStringToHandle(770 - 10 * digits1, 560, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", playerData->GetPlayerStatus()->GetMoney());
	DrawFormatStringToHandle(610, 560, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持金：");
}

void MenuTop::DrawCharacterStatus()
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

void MenuTop::Reset()
{
	pushFlag = false;
}