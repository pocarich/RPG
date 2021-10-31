#include"../header/MenuSynthesis.h"
#include"../header/KeyBoard.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"
#include"../header/ItemInfoList.h"
#include"../header/SynthesisInfoList.h"

GHandle MenuSynthesis::cursor;
GHandle MenuSynthesis::conditionErrorGraph[(int)ConditionError::SIZE];

MenuSynthesis::MenuSynthesis(PlayerData* playerData) :playerData(playerData)
{
	state = 0;
	cursorNum1 = 0;
	cursorNum2 = 0;
	offset = 0;
	closeFlag = false;

	UpdateTempItemList();
}

MenuSynthesis::~MenuSynthesis()
{

}

void MenuSynthesis::Load()
{
	cursor = LoadGraph("data/graph/cursor.png");
	assert(cursor != 0 && "MenuSynthesis::Load()");
	conditionErrorGraph[0] = LoadGraph("data/graph/ConditionError1.png");
	assert(conditionErrorGraph[0] != 0 && "MenuSynthesis::Load()");
	conditionErrorGraph[1] = LoadGraph("data/graph/ConditionError2.png");
	assert(conditionErrorGraph[1] != 0 && "MenuSynthesis::Load()");
	conditionErrorGraph[2] = LoadGraph("data/graph/ConditionError3.png");
	assert(conditionErrorGraph[2] != 0 && "MenuSynthesis::Load()");
}

void MenuSynthesis::UpdateTempItemList()
{
	tempItemList.clear();

	tempItemList = playerData->GetPlayerStatus()->GetHoldItemList();

	for (auto& obj : playerData->GetCharacterStatusList())
	{
		if (obj->GetWeapon() != -1)
		{
			tempItemList[obj->GetWeapon()]--;
		}
		if (obj->GetHead() != -1)
		{
			tempItemList[obj->GetHead()]--;
		}
		if (obj->GetChest() != -1)
		{
			tempItemList[obj->GetChest()]--;
		}
		if (obj->GetAccessory()[0] != -1)
		{
			tempItemList[obj->GetAccessory()[0]]--;
		}
		if (obj->GetAccessory()[1] != -1)
		{
			tempItemList[obj->GetAccessory()[1]]--;
		}
		if (obj->GetAccessory()[2] != -1)
		{
			tempItemList[obj->GetAccessory()[2]]--;
		}
	}
}

void MenuSynthesis::Update()
{
	MoveCursor();
	Push();
}

void MenuSynthesis::MoveCursor()
{
	switch (state)
	{
	case 0:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			if (cursorNum1 >= 1)
			{
				if (cursorNum1 - offset == 0)
				{
					offset --;
				}
				cursorNum1 --;
				cursorNum1 = max(0, cursorNum1);
			}
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			if ((cursorNum1 - offset == 11) && SynthesisInfoList::GetSynthesisInfoList().size() - offset >= 13)
			{
				offset ++;
			}
			cursorNum1 ++;
			cursorNum1 = min(SynthesisInfoList::GetSynthesisInfoList().size() - 1, cursorNum1);
		}
		break;
	case 1:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			cursorNum2 = (++cursorNum2) % 2;
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			cursorNum2 = (++cursorNum2) % 2;
		}
		break;
	}
}

void MenuSynthesis::Push()
{
	switch (state)
	{
	case 0:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			switch (CanSelect())
			{
			case 0:
				state = 1;
				break;
			case 1:
				state = 3;
				break;
			case 2:
				state = 2;
				break;
			}
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			closeFlag = true;
		}
		break;
	case 1:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			if (cursorNum2 == 0)
			{
				Synthesis();
			}
			
			state = 0;
			cursorNum2 = 0;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			cursorNum2 = 0;
			state = 0;
		}
		break;
	case 2:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 0;
		}
		break;
	case 3:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 0;
		}
		break;
	}
}

void MenuSynthesis::Synthesis()
{
	playerData->GetPlayerStatus()->AddItem(SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].itemKind);
	playerData->StandFlag(300 + cursorNum1);
	for (int i = 0; i != SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].neddIngredients.size(); i++)
	{
		for (int j = 0; j != SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].needNum[i]; j++)
		{
			playerData->GetPlayerStatus()->UseItem(SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].neddIngredients[i]);
		}
	}
	UpdateTempItemList();
}

void MenuSynthesis::Draw()
{
	Function::Alpha(100);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	DrawCharacterStatus();
	DrawTopic();

	if (state >= 0)
	{
		if (state >= 1)
		{
			Function::Alpha(200);
		}
		DrawFillBox(128, 8, 402, 402, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(130, 10, 400, 400, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 12); i++)
		{
			if (i < SynthesisInfoList::GetSynthesisInfoList().size())
			{
				if (cursorNum1 != i)
				{
					Function::Alpha(128);
				}
				if (playerData->GetHaveRecipe()[i])
				{
					DrawRotaGraph(155, 40 + itemGapLengthY*(i - offset), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[SynthesisInfoList::GetSynthesisInfoList()[i].itemKind].graphNum], TRUE);
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[SynthesisInfoList::GetSynthesisInfoList()[i].itemKind].name.c_str());
				}
				else
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "？？？？？");
				}
				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(265, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (SynthesisInfoList::GetSynthesisInfoList().size() - offset >= 13)
		{
			DrawRotaGraph(265, 390, 0.7, 0.0, cursor, TRUE);
		}
		Function::Alpha(255);
	}

	if (state >= 0)
	{
		if (state >= 1)
		{
			Function::Alpha(200);
		}

		DrawFillBox(408, 8, 772, 302, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(410, 10, 770, 300, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		if (playerData->GetHaveRecipe()[cursorNum1])
		{
			DrawFormatStringToHandle(Function::CalcCenterOfString(410, 770, FontMgr::GetFont()[11], "必要素材"), 30, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "必要素材");

			static const int itemGapLengthY = 30;

			for (int i = 0; i != SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].neddIngredients.size(); i++)
			{

				DrawRotaGraph(435, 80 + itemGapLengthY*i , 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].neddIngredients[i]].graphNum], TRUE);
				DrawFormatStringToHandle(455, 70 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].neddIngredients[i]].name.c_str());
				DrawFormatStringToHandle(600, 70 + itemGapLengthY*i , ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "×%d", SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].needNum[i]);
				if (SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].needNum[i] > tempItemList[SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].neddIngredients[i]])
				{
					DrawFormatStringToHandle(660, 70 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "所持数：%d", tempItemList[SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].neddIngredients[i]]);
				}
				else
				{
					DrawFormatStringToHandle(660, 70 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持数：%d", tempItemList[SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].neddIngredients[i]]);
				}
			}
		}
		else
		{
			DrawFormatStringToHandle(Function::CalcCenterOfString(410, 770, FontMgr::GetFont()[11], "レシピを持っていません"), 150, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "レシピを持っていません");
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
	{
		if (playerData->GetHaveRecipe()[cursorNum1])
		{
			static const int descriptionGapLengthY = 25;
			vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].itemKind].description, '|');
			for (int i = 0; i < 2; i++)
			{
				if (i < element.size())
				{
					DrawFormatStringToHandle(145, 420 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], element[i].c_str());
				}
			}
		}
	}
	break;
	case 1:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "本当に合成しますか？");
		break;
	case 2:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "素材が足りません。");
		break;
	case 3:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "このアイテムはこれ以上持てません。");
		break;
	}
}

void MenuSynthesis::DrawTopic()
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

void MenuSynthesis::DrawCharacterStatus()
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

int MenuSynthesis::CanSelect()
{
	if (playerData->GetPlayerStatus()->GetHoldItemList()[SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].itemKind] == ItemInfoList::GetItemInfoList()[SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].itemKind].maxHoldNum)
	{
		return 1;
	}
	for (int i = 0; i != SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].neddIngredients.size(); i++)
	{
		if (tempItemList[SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].neddIngredients[i]] < SynthesisInfoList::GetSynthesisInfoList()[cursorNum1].needNum[i])
		{
			return 2;
		}
	}
	return 0;
}