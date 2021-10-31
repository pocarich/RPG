#include"../header/MenuEquip.h"
#include"../header/KeyBoard.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"
#include"../header/ItemInfoList.h"

GHandle MenuEquip::downCursor;
GHandle MenuEquip::cursor;
GHandle MenuEquip::conditionErrorGraph[(int)ConditionError::SIZE];

MenuEquip::MenuEquip(PlayerData* playerData) :playerData(playerData)
{
	closeFlag = false;
	cursorNum1 = 0;
	cursorNum2 = 0;
	cursorNum3 = 0;
	offset = 0;
	state = 0;
	cursorTimer = 0;
}

MenuEquip::~MenuEquip()
{

}

void MenuEquip::Load()
{
	downCursor = LoadGraph("data/graph/down.png");
	assert(downCursor != 0 && "MenuEquip::Load()");
	cursor = LoadGraph("data/graph/cursor.png");
	assert(cursor != 0 && "MenuEquip::Load()");
	conditionErrorGraph[0] = LoadGraph("data/graph/ConditionError1.png");
	assert(conditionErrorGraph[0] != 0 && "MenuEquip::Load()");
	conditionErrorGraph[1] = LoadGraph("data/graph/ConditionError2.png");
	assert(conditionErrorGraph[1] != 0 && "MenuEquip::Load()");
	conditionErrorGraph[2] = LoadGraph("data/graph/ConditionError3.png");
	assert(conditionErrorGraph[2] != 0 && "MenuEquip::Load()");
}

void MenuEquip::UpdateTempItemList()
{
	tempItemList.clear();
	for (int i = 0; i != playerData->GetPlayerStatus()->GetHoldItemList().size(); i++)
	{
		switch (cursorNum2)
		{
		case 0:
		{
			if (playerData->GetPlayerStatus()->GetHoldItemList()[i] > 0 && find(playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipWeapon().begin(), playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipWeapon().end(), i) != playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipWeapon().end())
			{
				int n = playerData->GetPlayerStatus()->GetHoldItemList()[i];
				for (auto& obj : playerData->GetCharacterStatusList())
				{
					if (obj->GetWeapon() == i)
					{
						n--;
					}
				}
				if (n > 0)
				{
					tempItemList.push_back(i);
				}
			}
		}
			break;
		case 1:
		{
			if (playerData->GetPlayerStatus()->GetHoldItemList()[i] > 0 && find(playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipHead().begin(), playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipHead().end(), i) != playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipHead().end())
			{
				int n = playerData->GetPlayerStatus()->GetHoldItemList()[i];
				for (auto& obj : playerData->GetCharacterStatusList())
				{
					if (obj->GetHead() == i)
					{
						n--;
					}
				}
				if (n > 0)
				{
					tempItemList.push_back(i);
				}
			}
		}
			break;
		case 2:
		{
			if (playerData->GetPlayerStatus()->GetHoldItemList()[i] > 0 && find(playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipChest().begin(), playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipChest().end(), i) != playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipChest().end())
			{
				int n = playerData->GetPlayerStatus()->GetHoldItemList()[i];
				for (auto& obj : playerData->GetCharacterStatusList())
				{
					if (obj->GetChest() == i)
					{
						n--;
					}
				}
				if (n > 0)
				{
					tempItemList.push_back(i);
				}
			}
		}
			break;
		case 3:
		{
			if (playerData->GetPlayerStatus()->GetHoldItemList()[i] > 0 && find(playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipAccessory().begin(), playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipAccessory().end(), i) != playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipAccessory().end())
			{
				int n = playerData->GetPlayerStatus()->GetHoldItemList()[i];
				for (auto& obj : playerData->GetCharacterStatusList())
				{
					for (int j = 0; j < 3; j++)
					{
						if (obj->GetAccessory()[j] == i)
						{
							n--;
						}
					}
				}
				if (n > 0)
				{
					tempItemList.push_back(i);
				}
			}
		}
			break;
		case 4:
		{
			if (playerData->GetPlayerStatus()->GetHoldItemList()[i] > 0 && find(playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipAccessory().begin(), playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipAccessory().end(), i) != playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipAccessory().end())
			{
				int n = playerData->GetPlayerStatus()->GetHoldItemList()[i];
				for (auto& obj : playerData->GetCharacterStatusList())
				{
					for (int j = 0; j < 3; j++)
					{
						if (obj->GetAccessory()[j] == i)
						{
							n--;
						}
					}
				}
				if (n > 0)
				{
					tempItemList.push_back(i);
				}
			}
		}
			break;
		case 5:
		{
			if (playerData->GetPlayerStatus()->GetHoldItemList()[i] > 0 && find(playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipAccessory().begin(), playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipAccessory().end(), i) != playerData->GetCharacterStatusList()[cursorNum1]->GetCanEquipAccessory().end())
			{
				int n = playerData->GetPlayerStatus()->GetHoldItemList()[i];
				for (auto& obj : playerData->GetCharacterStatusList())
				{
					for (int j = 0; j < 3; j++)
					{
						if (obj->GetAccessory()[j] == i)
						{
							n--;
						}
					}
				}
				if (n > 0)
				{
					tempItemList.push_back(i);
				}
			}
		}
			break;
		}
	}
}

void MenuEquip::Update()
{
	MoveCursor();
	Push();
}

void MenuEquip::MoveCursor()
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
			cursorNum2--;
			cursorNum2 = max(0, cursorNum2);
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			cursorNum2++;
			cursorNum2 = min(5, cursorNum2);
		}
		if (KeyBoard::PushOnce(KEY_INPUT_C))
		{
			RemoveEquip();
		}
		break;
	case 2:
		if (tempItemList.size() != 0)
		{
			if (KeyBoard::PushOnce(KEY_INPUT_UP))
			{
				if (cursorNum3 >= 1)
				{
					if (cursorNum3 - offset == 0)
					{
						offset--;
					}
					cursorNum3--;
					cursorNum3 = max(0, cursorNum3);
				}
			}
			if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
			{
				if (cursorNum3 - offset == 11 && tempItemList.size() - offset >= 13)
				{
					offset ++;
				}
				cursorNum3 ++;
				cursorNum3 = min(tempItemList.size() - 1, cursorNum3);
			}
		}
		break;
	}
}

void MenuEquip::Push()
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
			state = 2;
			UpdateTempItemList();
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
			if (tempItemList.size() != 0)
			{
				SetEquip();
				cursorNum3 = 0;
				state = 1;
				offset = 0;
			}
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			cursorNum3 = 0;
			state = 1;
			offset = 0;
		}
		break;
	}
}

void MenuEquip::SetEquip()
{
	switch (cursorNum2)
	{
	case 0:
		playerData->GetCharacterStatusList()[cursorNum1]->SetWeapon(tempItemList[cursorNum3]);
		break;
	case 1:
		playerData->GetCharacterStatusList()[cursorNum1]->SetHead(tempItemList[cursorNum3]);
		break;
	case 2:
		playerData->GetCharacterStatusList()[cursorNum1]->SetChest(tempItemList[cursorNum3]);
		break;
	case 3:
		playerData->GetCharacterStatusList()[cursorNum1]->SetAccessory(0, tempItemList[cursorNum3]);
		break;
	case 4:
		playerData->GetCharacterStatusList()[cursorNum1]->SetAccessory(1, tempItemList[cursorNum3]);
		break;
	case 5:
		playerData->GetCharacterStatusList()[cursorNum1]->SetAccessory(2, tempItemList[cursorNum3]);
		break;
	}
}

void MenuEquip::RemoveEquip()
{
	switch (cursorNum2)
	{
	case 0:
		playerData->GetCharacterStatusList()[cursorNum1]->RemoveWeapon();
		break;
	case 1:
		playerData->GetCharacterStatusList()[cursorNum1]->RemoveHead();
		break;
	case 2:
		playerData->GetCharacterStatusList()[cursorNum1]->RemoveChest();
		break;
	case 3:
		playerData->GetCharacterStatusList()[cursorNum1]->RemoveAccessory(0);
		break;
	case 4:
		playerData->GetCharacterStatusList()[cursorNum1]->RemoveAccessory(1);
		break;
	case 5:
		playerData->GetCharacterStatusList()[cursorNum1]->RemoveAccessory(2);
		break;
	}
}

void MenuEquip::Draw()
{
	Function::Alpha(100);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	DrawCharacterStatus();
	DrawTopic();

	if (state >= 0)
	{
		if (state == 0 || state == 2)
		{
			Function::Alpha(200);
		}

		DrawFillBox(130, 10, 335, 220, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(132, 12, 333, 218, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		DrawRotaGraph(155, 40, 1.0, 0.0, ItemInfoList::GetGraph()[2], TRUE);
		DrawRotaGraph(155, 70, 1.0, 0.0, ItemInfoList::GetGraph()[12], TRUE);
		DrawRotaGraph(155, 100, 1.0, 0.0, ItemInfoList::GetGraph()[11], TRUE);
		DrawRotaGraph(155, 130, 1.0, 0.0, ItemInfoList::GetGraph()[15], TRUE);
		DrawRotaGraph(155, 160, 1.0, 0.0, ItemInfoList::GetGraph()[15], TRUE);
		DrawRotaGraph(155, 190, 1.0, 0.0, ItemInfoList::GetGraph()[15], TRUE);

		static const int itemGapLengthY = 30;

		for (int i = 0; i < 6; i++)
		{
			if (cursorNum2 != i)
			{
				Function::Alpha(128);
			}

			switch (i)
			{
			case 0:
				if (playerData->GetCharacterStatusList()[cursorNum1]->GetWeapon() != -1)
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetWeapon()].name.c_str());
				}
				else
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "装備なし");
				}
				break;
			case 1:
				if (playerData->GetCharacterStatusList()[cursorNum1]->GetHead() != -1)
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetHead()].name.c_str());
				}
				else
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "装備なし");
				}
				break;
			case 2:
				if (playerData->GetCharacterStatusList()[cursorNum1]->GetChest() != -1)
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetChest()].name.c_str());
				}
				else
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "装備なし");
				}
				break;
			case 3:
				if (playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[0] != -1)
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[0]].name.c_str());
				}
				else
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "装備なし");
				}
				break;
			case 4:
				if (playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[1] != -1)
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[1]].name.c_str());
				}
				else
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "装備なし");
				}
				break;
			case 5:
				if (playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[2] != -1)
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[2]].name.c_str());
				}
				else
				{
					DrawFormatStringToHandle(175, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "装備なし");
				}
				break;
			}
			Function::Alpha(255);
		}
	}

	if (state == 2)
	{
		DrawFillBox(345, 10, 550, 400, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(347, 12, 548, 398, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 12); i++)
		{
			if (i < tempItemList.size())
			{
				if (cursorNum3 != i)
				{
					Function::Alpha(128);
				}
				DrawRotaGraph(370, 40 + itemGapLengthY*(i - offset), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[tempItemList[i]].graphNum], TRUE);
				DrawFormatStringToHandle(390, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[tempItemList[i]].name.c_str());

				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(450, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (tempItemList.size() - offset >= 13)
		{
			DrawRotaGraph(450, 390, 0.7, 0.0, cursor, TRUE);
		}
		Function::Alpha(255);
	}

	if (state >= 0)
	{
		if (state == 0)
		{
			Function::Alpha(200);
		}

		DrawFillBox(560, 10, 770, 400, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(562, 12, 768, 398, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;
		static const string paramName[] = { "最大HP","最大SP","ATK","DEF","INT","RES" };
		for (int i = 0; i < 6; i++)
		{
			DrawFormatStringToHandle(Function::CalcCenterOfString(570,650, FontMgr::GetFont()[11], paramName[i].c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], paramName[i].c_str());
			DrawFormatStringToHandle(650, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ":");
			switch (i)
			{
			case 0:
			{
				stringstream ss;
				ss << playerData->GetCharacterStatusList()[cursorNum1]->GetMAX_HP();
				DrawFormatStringToHandle(Function::CalcCenterOfString(660, 700, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
			}
			break;
			case 1:
			{
				stringstream ss;
				ss << playerData->GetCharacterStatusList()[cursorNum1]->GetMAX_SP();
				DrawFormatStringToHandle(Function::CalcCenterOfString(660, 700, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
			}
			break;
			case 2:
			{
				stringstream ss;
				ss << playerData->GetCharacterStatusList()[cursorNum1]->GetATK();
				DrawFormatStringToHandle(Function::CalcCenterOfString(660, 700, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
			}
			break;
			case 3:
			{
				stringstream ss;
				ss << playerData->GetCharacterStatusList()[cursorNum1]->GetDEF();
				DrawFormatStringToHandle(Function::CalcCenterOfString(660, 700, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
			}
			break;
			case 4:
			{
				stringstream ss;
				ss << playerData->GetCharacterStatusList()[cursorNum1]->GetINT();
				DrawFormatStringToHandle(Function::CalcCenterOfString(660, 700, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
			}						break;
			case 5:
			{
				stringstream ss;
				ss << playerData->GetCharacterStatusList()[cursorNum1]->GetRES();
				DrawFormatStringToHandle(Function::CalcCenterOfString(660, 700, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
			}
			break;
			}

			if (state == 2 && tempItemList.size() != 0)
			{
				DrawFormatStringToHandle(700, 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "→");

				int changedNum;
				switch (cursorNum2)
				{
				case 0:
					changedNum = playerData->GetCharacterStatusList()[cursorNum1]->GetWeapon();
					break;
				case 1:
					changedNum = playerData->GetCharacterStatusList()[cursorNum1]->GetHead();
					break;
				case 2:
					changedNum = playerData->GetCharacterStatusList()[cursorNum1]->GetChest();
					break;
				case 3:
					changedNum = playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[0];
					break;
				case 4:
					changedNum = playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[1];
					break;
				case 5:
					changedNum = playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[2];
					break;
				}
				switch (i)
				{
				case 0:
				{
					int nextValue = playerData->GetCharacterStatusList()[cursorNum1]->GetMAX_HP() + ItemInfoList::GetItemInfoList()[tempItemList[cursorNum3]].HP;
					if (changedNum != -1)
					{
						nextValue -= ItemInfoList::GetItemInfoList()[changedNum].HP;
					}
					stringstream ss;
					ss << nextValue;
					if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetMAX_HP() == 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetMAX_HP() > 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLUE], FontMgr::GetFont()[11], ss.str().c_str());
					}
				}
				break;
				case 1:
				{
					int nextValue = playerData->GetCharacterStatusList()[cursorNum1]->GetMAX_SP() + ItemInfoList::GetItemInfoList()[tempItemList[cursorNum3]].SP;
					if (changedNum != -1)
					{
						nextValue -= ItemInfoList::GetItemInfoList()[changedNum].SP;
					}					
					stringstream ss;
					ss << nextValue;
					if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetMAX_SP() == 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetMAX_SP() > 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLUE], FontMgr::GetFont()[11], ss.str().c_str());
					}
				}
				break;
				case 2:
				{
					int nextValue = playerData->GetCharacterStatusList()[cursorNum1]->GetATK() + ItemInfoList::GetItemInfoList()[tempItemList[cursorNum3]].ATK;
					if (changedNum != -1)
					{
						nextValue -= ItemInfoList::GetItemInfoList()[changedNum].ATK;
					}
					stringstream ss;
					ss << nextValue;
					if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetATK() == 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetATK() > 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLUE], FontMgr::GetFont()[11], ss.str().c_str());
					}
				}
				break;
				case 3:
				{
					int nextValue = playerData->GetCharacterStatusList()[cursorNum1]->GetDEF() + ItemInfoList::GetItemInfoList()[tempItemList[cursorNum3]].DEF;
					if (changedNum != -1)
					{
						nextValue -= ItemInfoList::GetItemInfoList()[changedNum].DEF;
					}		
					stringstream ss;
					ss << nextValue;
					if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetDEF() == 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetDEF() > 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLUE], FontMgr::GetFont()[11], ss.str().c_str());
					}
				}
				break;
				case 4:
				{
					int nextValue = playerData->GetCharacterStatusList()[cursorNum1]->GetINT() + ItemInfoList::GetItemInfoList()[tempItemList[cursorNum3]].INT;
					if (changedNum != -1)
					{
						nextValue -= ItemInfoList::GetItemInfoList()[changedNum].INT;
					}		
					stringstream ss;
					ss << nextValue;
					if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetINT() == 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetINT() > 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLUE], FontMgr::GetFont()[11], ss.str().c_str());
					}
				}						
				break;
				case 5:
				{
					int nextValue = playerData->GetCharacterStatusList()[cursorNum1]->GetRES() + ItemInfoList::GetItemInfoList()[tempItemList[cursorNum3]].RES;
					if (changedNum != -1)
					{
						nextValue -= ItemInfoList::GetItemInfoList()[changedNum].RES;
					}		
					stringstream ss;
					ss << nextValue;
					if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetRES() == 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else if (nextValue - playerData->GetCharacterStatusList()[cursorNum1]->GetRES() > 0)
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], ss.str().c_str());
					}
					else
					{
						DrawFormatStringToHandle(Function::CalcCenterOfString(700, 780, FontMgr::GetFont()[11], ss.str().c_str()), 30 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLUE], FontMgr::GetFont()[11], ss.str().c_str());
					}
				}
				break;
				}
			}
		}

		Function::Alpha(255);
	}

	if (state == 0)
	{
		cursorTimer++;
		DrawRotaGraphF(100 + 190 * cursorNum1, 480 + ((cursorTimer / 2) % 11), 1.0, 0.0, downCursor, TRUE);
	}

	DrawFillBox(130, 410, 770, 475, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
	DrawFillBox(132, 412, 768, 473, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

	static const int descriptionGapLengthY = 25;

	switch (state)
	{
	case 0:
		DrawFormatStringToHandle(145, 420, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "キャラクターを選択してください。");
		break;
	case 1:
		switch (cursorNum2)
		{
		case 0:
			if (playerData->GetCharacterStatusList()[cursorNum1]->GetWeapon() != -1)
			{
				vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetWeapon()].description, '|');
				for (int i = 0; i < 2; i++)
				{
					if (i < element.size())
					{
						DrawFormatStringToHandle(145, 420 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], element[i].c_str());
					}
				}
				DrawFormatStringToHandle(660, 445 , ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "（C：外す）");
			}
			break;
		case 1:
			if (playerData->GetCharacterStatusList()[cursorNum1]->GetHead() != -1)
			{
				vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetHead()].description, '|');
				for (int i = 0; i < 2; i++)
				{
					if (i < element.size())
					{
						DrawFormatStringToHandle(145, 420 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], element[i].c_str());
					}
				}
			}
			break;
		case 2:
			if (playerData->GetCharacterStatusList()[cursorNum1]->GetChest() != -1)
			{
				vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetChest()].description, '|');
				for (int i = 0; i < 2; i++)
				{
					if (i < element.size())
					{
						DrawFormatStringToHandle(145, 420 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], element[i].c_str());
					}
				}
			}
			break;
		case 3:
			if (playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[0] != -1)
			{
				vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[0]].description, '|');
				for (int i = 0; i < 2; i++)
				{
					if (i < element.size())
					{
						DrawFormatStringToHandle(145, 420 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], element[i].c_str());
					}
				}
			}
			break;
		case 4:
			if (playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[1] != -1)
			{
				vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[1]].description, '|');
				for (int i = 0; i < 2; i++)
				{
					if (i < element.size())
					{
						DrawFormatStringToHandle(145, 420 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], element[i].c_str());
					}
				}
			}
			break;
		case 5:
			if (playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[2] != -1)
			{
				vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[playerData->GetCharacterStatusList()[cursorNum1]->GetAccessory()[2]].description, '|');
				for (int i = 0; i < 2; i++)
				{
					if (i < element.size())
					{
						DrawFormatStringToHandle(145, 420 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], element[i].c_str());
					}
				}
			}
			break;
		}
		break;
	case 2:
		if (tempItemList.size() != 0)
		{
			vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[tempItemList[cursorNum3]].description, '|');
			for (int i = 0; i < 2; i++)
			{
				if (i < element.size())
				{
					DrawFormatStringToHandle(145, 420 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], element[i].c_str());
				}
			}
		}
		break;
	}
}

void MenuEquip::DrawTopic()
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

void MenuEquip::DrawCharacterStatus()
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