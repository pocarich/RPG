#include"../header/MenuSkill.h"
#include"../header/KeyBoard.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"
#include"../header/CharacterSkillInfoList.h"
#include"../header/ItemInfoList.h"


GHandle MenuSkill::downCursor;
GHandle MenuSkill::cursor;
GHandle MenuSkill::keyGraph[3];
GHandle MenuSkill::conditionErrorGraph[(int)ConditionError::SIZE];

MenuSkill::MenuSkill(PlayerData* playerData) :playerData(playerData)
{
	closeFlag = false;
	cursorNum1 = 0;
	cursorNum2 = 0;
	cursorNum3 = 0;
	cursorNum4 = 0;
	offset = 0;
	state = 0;
	cursorTimer = 0;
}

MenuSkill::~MenuSkill()
{

}

void MenuSkill::Load()
{
	downCursor = LoadGraph("data/graph/down.png");
	assert(downCursor != 0 && "MenuSkill::Load()");
	cursor = LoadGraph("data/graph/cursor.png");
	assert(cursor != 0 && "MenuSkill::Load()");
	keyGraph[0] = LoadGraph("data/graph/a.png");
	assert(keyGraph[0] != 0 && "MenuSkill::Load()");
	keyGraph[1] = LoadGraph("data/graph/s.png");
	assert(keyGraph[1] != 0 && "MenuSkill::Load()");
	keyGraph[2] = LoadGraph("data/graph/d.png");
	assert(keyGraph[2] != 0 && "MenuSkill::Load()");
	conditionErrorGraph[0] = LoadGraph("data/graph/ConditionError1.png");
	assert(conditionErrorGraph[0] != 0 && "MenuSkill::Load()");
	conditionErrorGraph[1] = LoadGraph("data/graph/ConditionError2.png");
	assert(conditionErrorGraph[1] != 0 && "MenuSkill::Load()");
	conditionErrorGraph[2] = LoadGraph("data/graph/ConditionError3.png");
	assert(conditionErrorGraph[2] != 0 && "MenuSkill::Load()");
}

void MenuSkill::Update()
{
	MoveCursor();
	Push();
}

void MenuSkill::MoveCursor()
{
	switch (state)
	{
	case 0:
		if (playerData->GetExistCharacterFlag()[1])
		{
			if (KeyBoard::PushOnce(KEY_INPUT_LEFT))
			{
				cursorNum1 = (++cursorNum1) % playerData->GetCharacterStatusList().size();
			}
			if (KeyBoard::PushOnce(KEY_INPUT_RIGHT))
			{
				cursorNum1 = (++cursorNum1) % playerData->GetCharacterStatusList().size();
			}
		}
		break;
	case 1:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			if (cursorNum2 >= 1)
			{
				if (cursorNum2 - offset == 0)
				{
					offset --;
				}
				cursorNum2 --;
				cursorNum2 = max(0, cursorNum2);
			}
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			if (cursorNum2 - offset == 11 && playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList().size() - offset >= 13)
			{
				offset ++;
			}
			cursorNum2 ++;
			cursorNum2 = min(playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList().size() - 1, cursorNum2);
		}
		break;
	case 2:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			if (cursorNum4 >= 1)
			{
				cursorNum4--;
				cursorNum4 = max(0, cursorNum4);
			}
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			cursorNum4++;
			cursorNum4 = min(3, cursorNum4);
		}
		break;
	case 3:
		if (playerData->GetExistCharacterFlag()[1])
		{
			if (KeyBoard::PushOnce(KEY_INPUT_LEFT))
			{
				cursorNum3 = (++cursorNum3) % playerData->GetCharacterStatusList().size();
			}
			if (KeyBoard::PushOnce(KEY_INPUT_RIGHT))
			{
				cursorNum3 = (++cursorNum3) % playerData->GetCharacterStatusList().size();
			}
		}
		break;
	}
}

void MenuSkill::Push()
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
			if (playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList().size() != 0)
			{
				state = 2;
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
			switch (CanSelect())
			{
			case 0:
				break;
			case 1:
				state = 3;
				cursorNum4 = 0;
				break;
			case 2:
				playerData->GetCharacterStatusList()[cursorNum1]->SetSkill(cursorNum4 - 1, playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]);
				state = 1;
				cursorNum4 = 0;
				break;
			case 5:
				state = 5;
				break;
			case 6:
				state = 6;
				break;
			}
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			cursorNum4 = 0;
			state = 1;
		}
		break;
	case 3:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			switch (CanSelect2())
			{
			case 1:
				UseSkill();
				break;
			case 10:
				state = 10;
				cursorNum3 = 0;
				break;
			case 11:
				state = 11;
				break;
			case 12:
				state = 12;
				break;
			}
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			cursorNum3 = 0;
			state = 2;
		}
		break;
	case 5:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 2;
		}
		break;
	case 6:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 2;
		}
		break;
	case 10:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 1;
		}
		break;
	case 11:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 3;
		}
		break;
	case 12:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 3;
		}
		break;
	}
}

void MenuSkill::UseSkill()
{
	playerData->GetCharacterStatusList()[cursorNum1]->PaySP(playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]);
	playerData->GetCharacterStatusList()[cursorNum3]->CauseSkill(playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]);
}

void MenuSkill::Draw()
{
	Function::Alpha(100);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	DrawCharacterStatus();
	DrawTopic();

	if (state >= 1)
	{
		if (state >= 2)
		{
			Function::Alpha(200);
		}
		DrawFillBox(130, 10, 640, 400, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(132, 12, 638, 398, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 12); i++)
		{
			if (i < playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList().size())
			{
				if (cursorNum2 != i)
				{
					Function::Alpha(128);
				}
				DrawFormatStringToHandle(305, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "Lv %d", playerData->GetCharacterStatusList()[cursorNum1]->GetSkillLevel()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i]]);
				DrawFormatStringToHandle(165, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i]].name.c_str());

				int paySP = CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i]].paySP[playerData->GetCharacterStatusList()[cursorNum1]->GetSkillLevel()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i]] - 1];

				if (playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i] == 18)
				{
					paySP = playerData->GetCharacterStatusList()[cursorNum1]->GetMAX_SP() / 2;
				}

				int weapon = playerData->GetCharacterStatusList()[cursorNum1]->GetWeapon();
				paySP -= playerData->GetCharacterStatusList()[cursorNum1]->GetReduceSPUse();
				paySP = max(0, paySP);

				if (weapon != -1 && ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::REDUCE_PAY_MP_PERCENT] > 0.001)
				{
					paySP *= ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::REDUCE_PAY_MP_PERCENT];
				}

				DrawFormatStringToHandle(370, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "消費SP:%d", paySP);
				if (playerData->GetCharacterStatusList()[cursorNum1]->GetSkillLevel()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i]] == Define::PLAYER_SKILL_LEVEL_MAX)
				{
					DrawFormatStringToHandle(500, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "熟練度:MAX");
				}
				else
				{
					DrawFormatStringToHandle(500, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "熟練度:%d/%d", playerData->GetCharacterStatusList()[cursorNum1]->GetSkillEXP()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i]], CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i]].needPoint[playerData->GetCharacterStatusList()[cursorNum1]->GetSkillLevel()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i]] - 1]);
				}
				if (playerData->GetCharacterStatusList()[cursorNum1]->GetSetSkill()[0] == playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i])
				{
					DrawRotaGraph(150, 40 + itemGapLengthY*(i - offset), 0.8, 0.0, keyGraph[0], TRUE);
				}
				if (playerData->GetCharacterStatusList()[cursorNum1]->GetSetSkill()[1] == playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i])
				{
					DrawRotaGraph(150, 40 + itemGapLengthY*(i - offset), 0.8, 0.0, keyGraph[1], TRUE);
				}
				if (playerData->GetCharacterStatusList()[cursorNum1]->GetSetSkill()[2] == playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[i])
				{
					DrawRotaGraph(150, 40 + itemGapLengthY*(i - offset), 0.8, 0.0, keyGraph[2], TRUE);
				}
				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(385, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList().size() - offset >= 13)
		{
			DrawRotaGraph(385, 390, 0.7, 0.0, cursor, TRUE);
		}
		Function::Alpha(255);
	}
	if (state == 2 || state == 5 || state == 6)
	{
		if (state > 2)
		{
			Function::Alpha(200);
		}
		DrawFillBox(650, 250, 770, 400, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(652, 252, 768, 398, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;
		static const string topicMessage[] = { "使用する","Aにセット","Sにセット","Dにセット" };

		for (int i =0; i != 4; i++)
		{
			
				if (cursorNum4 != i)
				{
					Function::Alpha(128);
				}
				DrawFormatStringToHandle(670, 270 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], topicMessage[i].c_str());
				Function::Alpha(255);
		}
		Function::Alpha(255);
	}

	if (state == 0)
	{
		cursorTimer++;
		DrawRotaGraphF(100 + 190 * cursorNum1, 480 + ((cursorTimer / 2) % 11), 1.0, 0.0, downCursor, TRUE);
	}
	if (state == 3)
	{
		cursorTimer++;
		DrawRotaGraphF(100 + 190 * cursorNum3, 480 + ((cursorTimer / 2) % 11), 1.0, 0.0, downCursor, TRUE);
	}

	DrawFillBox(130, 410, 770, 475, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
	DrawFillBox(132, 412, 768, 473, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

	switch (state)
	{
	case 0:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "キャラクターを選択してください。");
		break;
	case 1:
	{
		if (playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList().size() > 0)
		{
			static const int descriptionGapLengthY = 25;
			vector<string> element = Function::split(CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]].description, '|');
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
	case 2:
	{
		if (playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList().size() > 0)
		{
			static const int descriptionGapLengthY = 25;
			vector<string> element = Function::split(CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]].description, '|');
			for (int i = 0; i < 2; i++)
			{
				if (i < element.size())
				{
					DrawFormatStringToHandle(145, 420 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], element[i].c_str());
				}
			}
		}
	}		break;
	case 3:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "使用するキャラクターを選択してください。");
		break;
	case 5:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "SPが足りません。");
		break;
	case 6:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "このスキルはセットできません。");
		break;
	case 10:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "SPが足りません。");
		break;
	case 11:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "HPが満タンです。");
		break;
	case 12:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "状態異常にかかっていません。");
		break;
	}
}

void MenuSkill::DrawTopic()
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

void MenuSkill::DrawCharacterStatus()
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

int MenuSkill::CanSelect()
{
	if (cursorNum4 == 0)
	{
		if (CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]].type == SkillType::ATTACK)
		{
			return 0;
		}

		int paySP = CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]].paySP[playerData->GetCharacterStatusList()[cursorNum1]->GetSkillLevel()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]] - 1];
		int weapon = playerData->GetCharacterStatusList()[cursorNum1]->GetWeapon();

		if (playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2] == 18)
		{
			paySP = playerData->GetCharacterStatusList()[cursorNum1]->GetMAX_SP() / 2;
		}

		paySP -= playerData->GetCharacterStatusList()[cursorNum1]->GetReduceSPUse();
		paySP = max(0, paySP);

		if (weapon != -1 && ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::REDUCE_PAY_MP_PERCENT] > 0.001)
		{
			paySP *= ItemInfoList::GetItemInfoList()[weapon].option[(int)ItemInfo::ItemOption::REDUCE_PAY_MP_PERCENT];
		}

		if (paySP > playerData->GetCharacterStatusList()[cursorNum1]->GetSP())
		{
			return 5;
		}
		if (CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]].type == SkillType::SUPPORT)
		{
			return 1;
		}
	}
	else
	{
		if (CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]].type == SkillType::SUPPORT)
		{
			return 6;
		}
		else
		{
			return 2;
		}
	}

	return -1;
}

int MenuSkill::CanSelect2()
{
	if (CharacterSkillInfoList::GetCharacterSkillInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]].paySP[playerData->GetCharacterStatusList()[cursorNum1]->GetSkillLevel()[playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2]] - 1]  > playerData->GetCharacterStatusList()[cursorNum1]->GetSP())
	{
		return 10;
	}

	auto status = playerData->GetCharacterStatusList()[cursorNum3];

	switch (playerData->GetCharacterStatusList()[cursorNum1]->GetLearnSkillList()[cursorNum2])
	{
	case 18:
		if (status->GetHP() == status->GetMAX_HP())
		{
			return 11;
		}
		break;
	case 19:
		if (find(status->GetConditionError().begin(), status->GetConditionError().end(), true) == status->GetConditionError().end())
		{
			return 12;
		}
		break;
	}

	return 1;
}