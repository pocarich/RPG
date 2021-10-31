#include"../header/INN.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"
#include"../header/FontMgr.h"
#include"../header/INNInfoList.h"
#include"../header/MessageWindow.h"
#include"../header/SelectWindow.h"

INN::INN(PlayerData* playerData, int INNKind) :playerData(playerData)
{
	this->INNKind = INNKind - Define::EVENT_INN_START;
	state = 0;
	closeFlag = false;
	darkAlpha = 0;
	INNTimer = 0;
}

void INN::Update()
{
	switch (state)
	{
	case 0:
		if (windowList.size() == 0)
		{
			windowList.push_back(make_shared<MessageWindow>(INNInfoList::GetINNInfoList()[INNKind].name, INNInfoList::GetINNInfoList()[INNKind].messages[0]));
		}
		if (windowList.back()->GetEndFlag())
		{
			windowList.clear();
			state++;
		}
		break;
	case 1:
		if (windowList.size() == 0)
		{
			windowList.push_back(make_shared<MessageWindow>(INNInfoList::GetINNInfoList()[INNKind].name, INNInfoList::GetINNInfoList()[INNKind].messages[1]));
			windowList.push_back(make_shared<SelectWindow>(SelectWindow::Type::NORMAL, 2, "ÇÕÇ¢/Ç¢Ç¢Ç¶"));
		}
		if (windowList.back()->GetEndFlag())
		{
			if (windowList.back()->GetData()[0] == 0)
			{
				if (playerData->GetPlayerStatus()->GetMoney() >= INNInfoList::GetINNInfoList()[INNKind].payMoney)
				{
					state++;
				}
				else
				{
					state = 3;
				}
			}
			else
			{
				state = 4;
			}
			windowList.clear();
		}
		break;
	case 2:
		UpdateINN();
		break;
	case 3:
		if (windowList.size() == 0)
		{
			windowList.push_back(make_shared<MessageWindow>(INNInfoList::GetINNInfoList()[INNKind].name, INNInfoList::GetINNInfoList()[INNKind].messages[2]));
		}
		if (windowList.back()->GetEndFlag())
		{
			windowList.clear();
			closeFlag = true;;
		}
		break;
	case 4:
		if (windowList.size() == 0)
		{
			windowList.push_back(make_shared<MessageWindow>(INNInfoList::GetINNInfoList()[INNKind].name, INNInfoList::GetINNInfoList()[INNKind].messages[3]));
		}
		if (windowList.back()->GetEndFlag())
		{
			windowList.clear();
			closeFlag = true;
		}
		break;
	}

	for (auto& obj : windowList)
	{
		obj->Update();
	}
}

void INN::UpdateINN()
{
	if (30 <= INNTimer&&INNTimer < 150)
	{
		darkAlpha += 255 / 60;
		darkAlpha = min(255, darkAlpha);
	}

	if (INNTimer == 150)
	{
		playerData->UseINN();
		playerData->GetPlayerStatus()->UseMoney(INNInfoList::GetINNInfoList()[INNKind].payMoney);
	}

	if (150 <= INNTimer&&INNTimer < 270)
	{
		darkAlpha -= 255 / 60;
		darkAlpha = max(0, darkAlpha);
	}

	if (INNTimer == 270)
	{
		state = 4;
	}

	INNTimer++;
}

void INN::Draw()
{
	for (auto& obj : windowList)
	{
		obj->Draw();
	}

	if (state == 1)
	{
		DrawFillBox(598, 8, 792, 52, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(600, 10, 790, 50, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		int digits1;
		if (playerData->GetPlayerStatus()->GetMoney() == 0)
		{
			digits1 = 0;
		}
		else
		{
			digits1 = (int)log10(playerData->GetPlayerStatus()->GetMoney());
		}

		DrawFormatStringToHandle(770 - 10 * digits1 - 18, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "Åè");
		DrawFormatStringToHandle(770 - 10 * digits1, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", playerData->GetPlayerStatus()->GetMoney());
		DrawFormatStringToHandle(610, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "èäéùã‡ÅF");
	}

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);
}