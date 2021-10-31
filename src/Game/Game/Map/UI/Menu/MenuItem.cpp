#include"../header/MenuItem.h"
#include"../header/KeyBoard.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"
#include"../header/ItemInfoList.h"

GHandle MenuItem::downCursor;
GHandle MenuItem::cursor;
GHandle MenuItem::conditionErrorGraph[(int)ConditionError::SIZE];

MenuItem::MenuItem(PlayerData* playerData) :playerData(playerData)
{
	closeFlag = false;
	cursorNum1 = 0;
	cursorNum2 = 0;
	cursorNum3 = 0;
	offset = 0;
	state = 0;
	cursorTimer = 0;
	UpdateTempItemList();
}

MenuItem::~MenuItem()
{

}

void MenuItem::Load()
{
	downCursor = LoadGraph("data/graph/down.png");
	assert(downCursor != 0 && "MenuItem::Load()");
	cursor = LoadGraph("data/graph/cursor.png");
	assert(cursor != 0 && "MenuItem::Load()");
	conditionErrorGraph[0] = LoadGraph("data/graph/ConditionError1.png");
	assert(conditionErrorGraph[0] != 0 && "MenuItem::Load()");
	conditionErrorGraph[1] = LoadGraph("data/graph/ConditionError2.png");
	assert(conditionErrorGraph[1] != 0 && "MenuItem::Load()");
	conditionErrorGraph[2] = LoadGraph("data/graph/ConditionError3.png");
	assert(conditionErrorGraph[2] != 0 && "MenuItem::Load()");
}

void MenuItem::UpdateTempItemList()
{
	tempItemList.clear();
	for (int i = 0; i != playerData->GetPlayerStatus()->GetHoldItemList().size(); i++)
	{
		if (playerData->GetPlayerStatus()->GetHoldItemList()[i] > 0)
		{
			tempItemList.push_back(pair<int, int>(i, playerData->GetPlayerStatus()->GetHoldItemList()[i]));
		}
	}
}

void MenuItem::Update()
{
	MoveCursor();
	Push();
}

void MenuItem::MoveCursor()
{
	if (tempItemList.size() == 0)
	{
		return;
	}

	switch (state)
	{
	case 0:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			if (cursorNum1 >= 2)
			{
				if (cursorNum1 - offset <= 1)
				{
					offset -= 2;
				}
				cursorNum1 -= 2;
				cursorNum1 = max(0, cursorNum1);
			}
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			if ((cursorNum1 - offset == 22 || cursorNum1 - offset == 23 )&& tempItemList.size() - offset >= 25)
			{
				offset += 2;
			}
			cursorNum1 += 2;
			cursorNum1 = min(tempItemList.size() - 1, cursorNum1);
		}
		if (KeyBoard::PushOnce(KEY_INPUT_LEFT))
		{
			if (cursorNum1 % 2 == 1)
			{
				cursorNum1--;
				cursorNum1 = max(0, cursorNum1);
			}
		}
		if (KeyBoard::PushOnce(KEY_INPUT_RIGHT))
		{
			if (cursorNum1 % 2 == 0)
			{
				cursorNum1 ++;
				cursorNum1 = min(tempItemList.size() - 1, cursorNum1);
			}
		}
		break;
	case 1:
		if (playerData->GetExistCharacterFlag()[1])
		{
			if (KeyBoard::PushOnce(KEY_INPUT_LEFT))
			{
				cursorNum2 = (++cursorNum2) % playerData->GetCharacterStatusList().size();
			}
			if (KeyBoard::PushOnce(KEY_INPUT_RIGHT))
			{
				cursorNum2 = (++cursorNum2) % playerData->GetCharacterStatusList().size();
			}
		}
		break;
	case 10:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{

			cursorNum3--;
			cursorNum3 = max(0, cursorNum3);

		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{

			cursorNum3++;
			cursorNum3 = min(1, cursorNum3);
		}
		break;
	}
}

void MenuItem::Push()
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
				state = 10;
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
			switch (CanUse())
			{
			case 0:
				UseItem();
				break;
			case 1:
				state = 2;
				break;
			case 2:
				state = 3;
				break;
			case 3:
				state = 4;
				break;
			case 4:
				state = 5;
				break;
			case 5:
				state = 6;
				break;
			case 6:
				state = 7;
				break;
			}
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
			state = 1;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 1;
		}
		break;
	case 3:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 1;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 1;
		}
		break;
	case 4:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 1;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 1;
		}
		break;
	case 5:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 1;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 1;
		}
		break;
	case 6:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 1;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 1;
		}
		break;
	case 7:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 1;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 1;
		}
		break;
	case 10:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			if (cursorNum3 == 0)
			{
				UseItemPlayer();
				state = 0;
				cursorNum3 = 0;
			}
			else
			{
				state = 0;
				cursorNum3 = 0;
			}
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 0;
			cursorNum3 = 0;
		}
		break;
	}
}

void MenuItem::UseItemPlayer()
{
	tempItemList[cursorNum1].second--;
	if (tempItemList[cursorNum1].second == 0)
	{
		tempItemList.erase(tempItemList.begin() + cursorNum1);
		cursorNum1 = min(cursorNum1, tempItemList.size() - 1);
		if (tempItemList.size() - offset <= 22)
		{
			offset -= 2;
			offset = max(0, offset);
		}
	}
}

void MenuItem::UseItem()
{
	playerData->GetCharacterStatusList()[cursorNum2]->UseItem(tempItemList[cursorNum1].first);
	tempItemList[cursorNum1].second--;
	playerData->GetPlayerStatus()->UseItem(tempItemList[cursorNum1].first);

	if (tempItemList[cursorNum1].second == 0)
	{
		cursorNum2 = 0;
		state = 0;
		tempItemList.erase(tempItemList.begin() + cursorNum1);
		cursorNum1 = min(cursorNum1, tempItemList.size() - 1);
		if (tempItemList.size() - offset <= 22)
		{
			offset -= 2;
			offset = max(0, offset);
		}
	}
}

void MenuItem::Draw()
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
		DrawFillBox(130, 10, 650, 400, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(132, 12, 648, 398, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthX = 250;
		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 24); i++)
		{
			if (i < tempItemList.size())
			{
				if (cursorNum1 != i)
				{
					Function::Alpha(128);
				}
				DrawRotaGraph(155 + itemGapLengthX*((i - offset) % 2 == 1), 40 + itemGapLengthY*((i - offset) / 2), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[tempItemList[i].first].graphNum], TRUE);
				DrawFormatStringToHandle(175 + itemGapLengthX*((i - offset) % 2 == 1), 30 + itemGapLengthY*((i - offset) / 2), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[tempItemList[i].first].name.c_str());

				int digits1=(int)log10(tempItemList[i].second);
				
				if (tempItemList[i].second == ItemInfoList::GetItemInfoList()[tempItemList[i].first].maxHoldNum)
				{
					DrawFormatStringToHandle(370 - 10 * digits1 - 18 + itemGapLengthX*((i - offset) % 2 == 1), 30 + itemGapLengthY*((i - offset) / 2), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "×");
					DrawFormatStringToHandle(370 - 10 * digits1 + itemGapLengthX*((i - offset) % 2 == 1), 30 + itemGapLengthY*((i - offset) / 2), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "%d", tempItemList[i].second);
				}
				else
				{
					DrawFormatStringToHandle(370 - 10 * digits1 - 18 + itemGapLengthX*((i - offset) % 2 == 1), 30 + itemGapLengthY*((i - offset) / 2), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "×");
					DrawFormatStringToHandle(370 - 10 * digits1 + itemGapLengthX*((i - offset) % 2 == 1), 30 + itemGapLengthY*((i - offset) / 2), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", tempItemList[i].second);
				}

				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(375, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (tempItemList.size() - offset >= 25)
		{
			DrawRotaGraph(375, 390, 0.7, 0.0, cursor, TRUE);
		}
		Function::Alpha(255);
	}

	if (state == 1)
	{
		cursorTimer++;
		DrawRotaGraphF(100 + 190 * cursorNum2, 480 + ((cursorTimer/2) % 11), 1.0, 0.0, downCursor, TRUE);
	}

	DrawFillBox(130, 410, 770, 475, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
	DrawFillBox(132, 412, 768, 473, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

	switch (state)
	{
	case 0:
	{
		if (tempItemList.size() > 0)
		{
			static const int descriptionGapLengthY = 25;
			vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[tempItemList[cursorNum1].first].description, '|');
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
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "使用するキャラクターを選択してください。");
		break;
	case 2:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "HPが満タンです。");
		break;
	case 3:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "SPが満タンです。");
		break;
	case 4:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "状態異常にかかっていません。");
		break;
	case 5:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "戦闘不能ではありません。");
		break;
	case 6:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "戦闘不能のキャラクタには使用できません。");
		break;
	case 7:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "HP・MPがともに満タンです。");
		break;
	case 10:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "このアイテムを使用しますか？");
		break;
	}

	if (state == 10)
	{
		static const int itemGapLengthY = 30;

		DrawFillBox(680, 320, 770, 400, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(682, 322, 768, 398, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		for (int i = 0; i < 2; i++)
		{
			if (cursorNum3 != i)
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
}

void MenuItem::DrawTopic()
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

void MenuItem::DrawCharacterStatus()
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

int MenuItem::CanSelect()
{
	if (tempItemList.size() == 0|| ItemInfoList::GetItemInfoList()[tempItemList[cursorNum1].first].type != ItemInfo::ItemType::USE)
	{
		return -1;
	}
	if (ItemInfoList::GetItemInfoList()[tempItemList[cursorNum1].first].option[(int)ItemInfo::ItemOption::STOP_TIME]>0.001)
	{
		return 1;
	}
	return 0;
}

int MenuItem::CanUse()
{
	if (tempItemList.size() == 0)
	{
		return -1;
	}

	auto info = ItemInfoList::GetItemInfoList()[tempItemList[cursorNum1].first];
	auto status = playerData->GetCharacterStatusList()[cursorNum2];

	if (info.option[(int)ItemInfo::ItemOption::REVIVAL]>0.001)
	{
		if (status->GetHP() != 0)
		{
			return 4;
		}
	}
	else
	{
		if (status->GetHP() == 0)
		{
			return 5;
		}
	}

	if (info.option[(int)ItemInfo::ItemOption::HP_HEAL_VALUE] > 0.001)
	{
		if (status->GetHP() == status->GetMAX_HP())
		{
			return 1;
		}
	}

	if (info.option[(int)ItemInfo::ItemOption::MP_HEAL_VALUE] > 0.001)
	{
		if (status->GetSP() == status->GetMAX_SP())
		{
			return 2;
		}
	}

	if (info.option[(int)ItemInfo::ItemOption::CURE_ALL_CONDITIONERROR])
	{
		if (find(status->GetConditionError().begin(), status->GetConditionError().end(), true) == status->GetConditionError().end())
		{
			return 3;
		}
	}

	if (info.option[(int)ItemInfo::ItemOption::HEAL_MAX] && info.option[(int)ItemInfo::ItemOption::ATK_UP_TIME] < 0.001)
	{
		if (status->GetSP() == status->GetMAX_SP()&& status->GetHP() == status->GetMAX_HP())
		{
			return 6;
		}
	}

	return 0;
}

