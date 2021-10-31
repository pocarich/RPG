#include"../header/Shop.h"
#include"../header/MessageWindow.h"
#include"../header/KeyBoard.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"
#include"../header/ItemInfoList.h"
#include"../header/ShopInfoList.h"

GHandle Shop::cursor;

Shop::Shop(PlayerData* playerData, int shopNum) :playerData(playerData)
{
	this->shopNum = shopNum - Define::EVENT_SHOP_START;
	cursorNum1 = 0;
	cursorNum2 = 1;
	cursorNum3 = 0;
	cursorNum4 = 0;
	offset = 0;
	closeFlag = false;
	state = 0;
}

Shop::~Shop()
{

}

void Shop::Load()
{
	cursor = LoadGraph("data/graph/cursor.png");
	assert(cursor != 0 && "MenuItem::Load()");
}

void Shop::UpdateTempItemList()
{
	tempItemList.clear();
	for (int i = 0; i != playerData->GetPlayerStatus()->GetHoldItemList().size(); i++)
	{
		if (playerData->GetPlayerStatus()->GetHoldItemList()[i] > 0 && ItemInfoList::GetItemInfoList()[i].sellMoney > 0)
		{
			tempItemList.push_back(pair<int, int>(i, playerData->GetPlayerStatus()->GetHoldItemList()[i]));
		}
	}
}

void Shop::Update()
{
	switch (state)
	{
	case 0:
		if (windowList.size() == 0)
		{
			windowList.push_back(make_shared<MessageWindow>(ShopInfoList::GetShopInfoList()[shopNum].name, ShopInfoList::GetShopInfoList()[shopNum].message[0]));
		}
		if (windowList.back()->GetEndFlag())
		{
			windowList.clear();
			state = 5;
		}
		break;
	case -1:
		if (windowList.size() == 0)
		{
			windowList.push_back(make_shared<MessageWindow>(ShopInfoList::GetShopInfoList()[shopNum].name, ShopInfoList::GetShopInfoList()[shopNum].message[1]));
		}
		if (windowList.back()->GetEndFlag())
		{
			windowList.clear();
			closeFlag = true;
		}
		break;
	default:
		MoveCursor();
		Push();
		break;
	}

	if (windowList.size() != 0)
	{
		windowList.back()->Update();
	}
}

void Shop::MoveCursor()
{
	switch (state)
	{
	case 1:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			if (cursorNum1 >= 1)
			{
				if (cursorNum1 - offset == 0)
				{
					offset--;
				}
				cursorNum1--;
				cursorNum1 = max(0, cursorNum1);
			}
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			if ((cursorNum1 - offset == 14) && ShopInfoList::GetShopInfoList()[shopNum].itemList.size() - offset >= 16)
			{
				offset++;
			}
			cursorNum1++;
			cursorNum1 = min(ShopInfoList::GetShopInfoList()[shopNum].itemList.size() - 1, cursorNum1);
		}
		break;
	case 2:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			cursorNum2 = (++cursorNum2) % (ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].maxHoldNum - playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]] + 1);
			if (cursorNum2 == 0)
			{
				cursorNum2 = 1;
			}
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			cursorNum2 = (cursorNum2 + (ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].maxHoldNum - playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]])) % (ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].maxHoldNum - playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]] + 1);
			if (cursorNum2 == 0)
			{
				cursorNum2 = (ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].maxHoldNum - playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]]);
			}
		}
		break;
	case 3:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			cursorNum3 = (++cursorNum3) % 2;
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			cursorNum3 = (++cursorNum3) % 2;
		}
		break;
	case 5:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			cursorNum4 = (++cursorNum4) % 2;
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			cursorNum4 = (++cursorNum4) % 2;
		}
		break;
	case 7:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			if (cursorNum1 >= 1)
			{
				if (cursorNum1 - offset == 0)
				{
					offset--;
				}
				cursorNum1--;
				cursorNum1 = max(0, cursorNum1);
			}
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			if ((cursorNum1 - offset == 14) && tempItemList.size() - offset >= 16)
			{
				offset++;
			}
			cursorNum1++;
			cursorNum1 = min(tempItemList.size() - 1, cursorNum1);
		}
		break;
	case 8:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			cursorNum2 = (++cursorNum2) % (tempItemList[cursorNum1].second + 1);
			if (cursorNum2 == 0)
			{
				cursorNum2 = 1;
			}
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			cursorNum2 = (cursorNum2 + tempItemList[cursorNum1].second) % (tempItemList[cursorNum1].second + 1);
			if (cursorNum2 == 0)
			{
				cursorNum2 = tempItemList[cursorNum1].second;
			}
		}
		break;
	case 9:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))
		{
			cursorNum3 = (++cursorNum3) % 2;
		}
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
		{
			cursorNum3 = (++cursorNum3) % 2;
		}
		break;
	}
}

void Shop::Push()
{
	switch (state)
	{
	case 1:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			if (playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]] == ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].maxHoldNum)
			{
				state = 6;
			}
			else
			{
				state = 2;
			}
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 5;
			cursorNum1 = 0;
		}
		break;
	case 2:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			if (ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].buyMoney*cursorNum2 <= playerData->GetPlayerStatus()->GetMoney())
			{
				state = 3;
			}
			else
			{
				state = 4;
			}
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 1;
			cursorNum2 = 1;
		}
		break;
	case 3:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			if (cursorNum3 == 0)
			{
				BuyItem();
				state = 1;
				cursorNum2 = 1;
			}
			else
			{
				state = 2;
			}
			cursorNum3 = 0;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 2;
			cursorNum3 = 0;
		}
		break;
	case 4:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 2;
		}
		break;
	case 5:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			if (cursorNum4 % 2 == 0)
			{
				state = 1;
			}
			else
			{
				UpdateTempItemList();
				state = 7;
			}
			cursorNum3 = 0;
		}
		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = -1;
		}
		break;
	case 6:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 1;
		}
		break;
	case 7:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			if (tempItemList.size() != 0)
			{
				state = 8;
			}
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 5;
			cursorNum1 = 0;
		}
		break;
	case 8:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			state = 9;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 7;
			cursorNum2 = 1;
		}
		break;
	case 9:
		if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			if (cursorNum3 == 0)
			{
				SellItem();
				state = 7;
				cursorNum2 = 1;
			}
			else
			{
				state = 8;
			}
			cursorNum3 = 0;
		}

		if (KeyBoard::PushOnce(KEY_INPUT_X))
		{
			state = 8;
			cursorNum3 = 0;
		}
		break;
	}
}

void Shop::BuyItem()
{
	for (int i = 0; i < cursorNum2; i++)
	{
		playerData->GetPlayerStatus()->AddItem(ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]);
	}
	playerData->GetPlayerStatus()->UseMoney(ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].buyMoney*cursorNum2);
}

void Shop::SellItem()
{
	tempItemList[cursorNum1].second--;
	playerData->GetPlayerStatus()->SellItem(tempItemList[cursorNum1].first);

	if (tempItemList[cursorNum1].second == 0)
	{
		tempItemList.erase(tempItemList.begin() + cursorNum1);
		cursorNum1 = min(cursorNum1, tempItemList.size() - 1);
		if (tempItemList.size() - offset <= 14)
		{
			offset --;
			offset = max(0, offset);
		}
	}
}

void Shop::Draw()
{
	switch (state)
	{
	case -1:
		break;
	case 0:
		break;
	case 1:
	{
		Function::Alpha(100);
		DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);


		DrawFillBox(8, 8, 452, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 10, 450, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 15); i++)
		{
			if (i < ShopInfoList::GetShopInfoList()[shopNum].itemList.size())
			{
				if (cursorNum1 != i)
				{
					Function::Alpha(128);
				}
				DrawRotaGraph(40, 40 + itemGapLengthY*(i - offset), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].graphNum], TRUE);
				DrawFormatStringToHandle(60, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].name.c_str());

				DrawFormatStringToHandle(250, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥%d", ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].buyMoney);

				if (playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]] == ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].maxHoldNum)
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]]);
				}
				else
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]]);
				}
				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(205, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (ShopInfoList::GetShopInfoList()[shopNum].itemList.size() - offset >= 16)
		{
			DrawRotaGraph(205, 480, 0.7, 0.0, cursor, TRUE);
		}

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

		DrawFormatStringToHandle(770 - 10 * digits1 - 18, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
		DrawFormatStringToHandle(770 - 10 * digits1, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", playerData->GetPlayerStatus()->GetMoney());
		DrawFormatStringToHandle(610, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持金：");

		DrawFillBox(8, 498, 792, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 500, 790, 590, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		if (ShopInfoList::GetShopInfoList()[shopNum].itemList.size() > 0)
		{
			static const int descriptionGapLengthY = 25;
			vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].description, '|');
			for (int i = 0; i < 2; i++)
			{
				if (i < element.size())
				{
					DrawFormatStringToHandle(25, 509 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], element[i].c_str());
				}
			}
		}
	}
	break;
	case 2:
	{
		Function::Alpha(100);
		DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);

		Function::Alpha(200);

		DrawFillBox(8, 8, 452, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 10, 450, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 15); i++)
		{
			if (i < ShopInfoList::GetShopInfoList()[shopNum].itemList.size())
			{
				if (cursorNum1 != i)
				{
					Function::Alpha(128);
				}
				DrawRotaGraph(40, 40 + itemGapLengthY*(i - offset), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].graphNum], TRUE);
				DrawFormatStringToHandle(60, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].name.c_str());

				DrawFormatStringToHandle(200, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥%d", ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].buyMoney);

				if (playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]] == ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].maxHoldNum)
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]]);
				}
				else
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]]);
				}
				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(205, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (ShopInfoList::GetShopInfoList()[shopNum].itemList.size() - offset >= 16)
		{
			DrawRotaGraph(205, 480, 0.7, 0.0, cursor, TRUE);
		}

		DrawFillBox(598, 8, 792, 52, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(600, 10, 790, 50, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		{
			int digits1;
			if (playerData->GetPlayerStatus()->GetMoney() == 0)
			{
				digits1 = 0;
			}
			else
			{
				digits1 = (int)log10(playerData->GetPlayerStatus()->GetMoney());
			}

			DrawFormatStringToHandle(770 - 10 * digits1 - 18, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
			DrawFormatStringToHandle(770 - 10 * digits1, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", playerData->GetPlayerStatus()->GetMoney());
			DrawFormatStringToHandle(610, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持金：");
		}

		DrawFillBox(598, 398, 792, 442, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(600, 400, 790, 440, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		int sum = ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].buyMoney*cursorNum2;
		int digits1;
		if (sum == 0)
		{
			digits1 = 0;
		}
		else
		{
			digits1 = (int)log10(sum);
		}

		if (sum <= playerData->GetPlayerStatus()->GetMoney())
		{
			DrawFormatStringToHandle(770 - 10 * digits1 - 18, 410, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
			DrawFormatStringToHandle(770 - 10 * digits1, 410, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", sum);
			DrawFormatStringToHandle(610, 410, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "合計：");
		}
		else
		{
			DrawFormatStringToHandle(770 - 10 * digits1 - 18, 410, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "￥");
			DrawFormatStringToHandle(770 - 10 * digits1, 410, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "%d", sum);
			DrawFormatStringToHandle(610, 410, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "合計：");
		}

		DrawFillBox(598, 448, 792, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(600, 450, 790, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		if (cursorNum2 == (ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].maxHoldNum - playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]]))
		{
			DrawFormatStringToHandle(610, 460, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "個数：");
			DrawFormatStringToHandle(740, 460, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "×%s", Function::NumToStringFillZero(cursorNum2, 2).c_str());
		}
		else
		{
			DrawFormatStringToHandle(610, 460, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "個数：");
			DrawFormatStringToHandle(740, 460, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "×%s", Function::NumToStringFillZero(cursorNum2, 2).c_str());
		}

		DrawFillBox(8, 498, 792, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 500, 790, 590, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		DrawFormatStringToHandle(25, 509, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], "購入する個数を選択してください。");
	}
	break;
	case 3:
	{
		Function::Alpha(100);
		DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);

		Function::Alpha(200);

		DrawFillBox(8, 8, 452, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 10, 450, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 15); i++)
		{
			if (i < ShopInfoList::GetShopInfoList()[shopNum].itemList.size())
			{
				if (cursorNum1 != i)
				{
					Function::Alpha(128);
				}
				DrawRotaGraph(40, 40 + itemGapLengthY*(i - offset), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].graphNum], TRUE);
				DrawFormatStringToHandle(60, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].name.c_str());

				DrawFormatStringToHandle(200, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥%d", ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].buyMoney);

				if (playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]] == ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].maxHoldNum)
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]]);
				}
				else
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]]);
				}
				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(205, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (ShopInfoList::GetShopInfoList()[shopNum].itemList.size() - offset >= 16)
		{
			DrawRotaGraph(205, 480, 0.7, 0.0, cursor, TRUE);
		}

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

		DrawFormatStringToHandle(770 - 10 * digits1 - 18, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
		DrawFormatStringToHandle(770 - 10 * digits1, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", playerData->GetPlayerStatus()->GetMoney());
		DrawFormatStringToHandle(610, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持金：");

		DrawFillBox(708, 408, 792, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(710, 410, 790, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		for (int i = 0; i < 2; i++)
		{
			if (cursorNum3 != i)
			{
				Function::Alpha(128);
			}

			switch (i)
			{
			case 0:
				DrawFormatStringToHandle(725, 425 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "はい");
				break;
			case 1:
				DrawFormatStringToHandle(725, 425 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "いいえ");
				break;
			}
			Function::Alpha(255);
		}

		DrawFillBox(8, 498, 792, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 500, 790, 590, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		DrawFormatStringToHandle(25, 509, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], "合計￥%dになります。本当に購入しますか？", ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].buyMoney*cursorNum2);
	}
	break;
	case 4:
	{
		Function::Alpha(100);
		DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);

		Function::Alpha(200);

		DrawFillBox(8, 8, 452, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 10, 450, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 15); i++)
		{
			if (i < ShopInfoList::GetShopInfoList()[shopNum].itemList.size())
			{
				if (cursorNum1 != i)
				{
					Function::Alpha(128);
				}
				DrawRotaGraph(40, 40 + itemGapLengthY*(i - offset), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].graphNum], TRUE);
				DrawFormatStringToHandle(60, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].name.c_str());

				DrawFormatStringToHandle(200, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥%d", ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].buyMoney);

				if (playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]] == ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].maxHoldNum)
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]]);
				}
				else
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]]);
				}
				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(205, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (ShopInfoList::GetShopInfoList()[shopNum].itemList.size() - offset >= 16)
		{
			DrawRotaGraph(205, 480, 0.7, 0.0, cursor, TRUE);
		}
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

		DrawFormatStringToHandle(770 - 10 * digits1 - 18, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
		DrawFormatStringToHandle(770 - 10 * digits1, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", playerData->GetPlayerStatus()->GetMoney());
		DrawFormatStringToHandle(610, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持金：");

		DrawFillBox(8, 498, 792, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 500, 790, 590, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		DrawFormatStringToHandle(25, 509, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], "お金が足りません。");
	}
	break;
	case 5:
	{
		Function::Alpha(100);
		DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);

		DrawFillBox(8, 8, 102, 102, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 10, 100, 100, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const string topic[] = { "買う","売る" };
		static const int topicGapLengthY = 35;
		for (int i = 0; i < 2; i++)
		{
			if (cursorNum4 != i)
			{
				Function::Alpha(128);
			}
			DrawFormatStringToHandle(Function::CalcCenterOfString(10, 100, FontMgr::GetFont()[11], topic[i].c_str()), 27 + topicGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], topic[i].c_str());

			Function::Alpha(255);
		}
	}
	break;
	case 6:
	{
		Function::Alpha(100);
		DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);

		Function::Alpha(200);

		DrawFillBox(8, 8, 452, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 10, 450, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 15); i++)
		{
			if (i < ShopInfoList::GetShopInfoList()[shopNum].itemList.size())
			{
				if (cursorNum1 != i)
				{
					Function::Alpha(128);
				}
				DrawRotaGraph(40, 40 + itemGapLengthY*(i - offset), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].graphNum], TRUE);
				DrawFormatStringToHandle(60, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].name.c_str());

				DrawFormatStringToHandle(200, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥%d", ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]].buyMoney);

				if (playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]] == ItemInfoList::GetItemInfoList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[cursorNum1]].maxHoldNum)
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]]);
				}
				else
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[ShopInfoList::GetShopInfoList()[shopNum].itemList[i]]);
				}
				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(205, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (ShopInfoList::GetShopInfoList()[shopNum].itemList.size() - offset >= 16)
		{
			DrawRotaGraph(205, 480, 0.7, 0.0, cursor, TRUE);
		}
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

		DrawFormatStringToHandle(770 - 10 * digits1 - 18, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
		DrawFormatStringToHandle(770 - 10 * digits1, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", playerData->GetPlayerStatus()->GetMoney());
		DrawFormatStringToHandle(610, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持金：");

		DrawFillBox(8, 498, 792, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 500, 790, 590, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		DrawFormatStringToHandle(25, 509, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], "このアイテムはこれ以上所持できません。");
	}
	break;
	case 7:
	{
		Function::Alpha(100);
		DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);


		DrawFillBox(8, 8, 452, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 10, 450, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 15); i++)
		{
			if (i < tempItemList.size())
			{
				if (cursorNum1 != i)
				{
					Function::Alpha(128);
				}
				DrawRotaGraph(40, 40 + itemGapLengthY*(i - offset), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[tempItemList[i].first].graphNum], TRUE);
				DrawFormatStringToHandle(60, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[tempItemList[i].first].name.c_str());

				DrawFormatStringToHandle(200, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥%d", ItemInfoList::GetItemInfoList()[tempItemList[i].first].sellMoney);

				if (playerData->GetPlayerStatus()->GetHoldItemList()[tempItemList[i].first] == ItemInfoList::GetItemInfoList()[tempItemList[i].first].maxHoldNum)
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[tempItemList[i].first]);
				}
				else
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[tempItemList[i].first]);
				}
				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(205, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (tempItemList.size() - offset >= 16)
		{
			DrawRotaGraph(205, 480, 0.7, 0.0, cursor, TRUE);
		}

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

		DrawFormatStringToHandle(770 - 10 * digits1 - 18, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
		DrawFormatStringToHandle(770 - 10 * digits1, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", playerData->GetPlayerStatus()->GetMoney());
		DrawFormatStringToHandle(610, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持金：");

		DrawFillBox(8, 498, 792, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 500, 790, 590, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		if (tempItemList.size() > 0)
		{
			static const int descriptionGapLengthY = 25;
			vector<string> element = Function::split(ItemInfoList::GetItemInfoList()[tempItemList[cursorNum1].first].description, '|');
			for (int i = 0; i < 2; i++)
			{
				if (i < element.size())
				{
					DrawFormatStringToHandle(25, 509 + descriptionGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], element[i].c_str());
				}
			}
		}
	}
	break;
	case 8:
	{
		Function::Alpha(100);
		DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);

		Function::Alpha(200);

		DrawFillBox(8, 8, 452, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 10, 450, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 15); i++)
		{
			if (i < tempItemList.size())
			{
				if (cursorNum1 != i)
				{
					Function::Alpha(128);
				}
				DrawRotaGraph(40, 40 + itemGapLengthY*(i - offset), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[tempItemList[i].first].graphNum], TRUE);
				DrawFormatStringToHandle(60, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[tempItemList[i].first].name.c_str());

				DrawFormatStringToHandle(200, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥%d", ItemInfoList::GetItemInfoList()[tempItemList[i].first].sellMoney);

				if (playerData->GetPlayerStatus()->GetHoldItemList()[tempItemList[i].first] == ItemInfoList::GetItemInfoList()[tempItemList[i].first].maxHoldNum)
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[tempItemList[i].first]);
				}
				else
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[tempItemList[i].first]);
				}
				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(205, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (tempItemList.size() - offset >= 16)
		{
			DrawRotaGraph(205, 480, 0.7, 0.0, cursor, TRUE);
		}

		DrawFillBox(598, 8, 792, 52, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(600, 10, 790, 50, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		{
			int digits1;
			if (playerData->GetPlayerStatus()->GetMoney() == 0)
			{
				digits1 = 0;
			}
			else
			{
				digits1 = (int)log10(playerData->GetPlayerStatus()->GetMoney());
			}

			DrawFormatStringToHandle(770 - 10 * digits1 - 18, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
			DrawFormatStringToHandle(770 - 10 * digits1, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", playerData->GetPlayerStatus()->GetMoney());
			DrawFormatStringToHandle(610, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持金：");
		}

		DrawFillBox(598, 398, 792, 442, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(600, 400, 790, 440, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		int sum = ItemInfoList::GetItemInfoList()[tempItemList[cursorNum1].first].sellMoney*cursorNum2;
		int digits1;
		if (sum == 0)
		{
			digits1 = 0;
		}
		else
		{
			digits1 = (int)log10(sum);
		}

		DrawFormatStringToHandle(770 - 10 * digits1 - 18, 410, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
		DrawFormatStringToHandle(770 - 10 * digits1, 410, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", sum);
		DrawFormatStringToHandle(610, 410, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "合計：");

		DrawFillBox(598, 448, 792, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(600, 450, 790, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		if (cursorNum2 == playerData->GetPlayerStatus()->GetHoldItemList()[tempItemList[cursorNum1].first])
		{
			DrawFormatStringToHandle(610, 460, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "個数：");
			DrawFormatStringToHandle(740, 460, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "×%s", Function::NumToStringFillZero(cursorNum2, 2).c_str());
		}
		else
		{
			DrawFormatStringToHandle(610, 460, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "個数：");
			DrawFormatStringToHandle(740, 460, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "×%s", Function::NumToStringFillZero(cursorNum2, 2).c_str());
		}

		DrawFillBox(8, 498, 792, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 500, 790, 590, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		DrawFormatStringToHandle(25, 509, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], "売却する個数を選択してください。");
	}
	break;
	case 9:
	{
		Function::Alpha(100);
		DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
		Function::Alpha(255);

		Function::Alpha(200);

		DrawFillBox(8, 8, 452, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 10, 450, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		static const int itemGapLengthY = 30;

		for (int i = offset; i != (offset + 15); i++)
		{
			if (i < tempItemList.size())
			{
				if (cursorNum1 != i)
				{
					Function::Alpha(128);
				}
				DrawRotaGraph(40, 40 + itemGapLengthY*(i - offset), 0.9, 0.0, ItemInfoList::GetGraph()[ItemInfoList::GetItemInfoList()[tempItemList[i].first].graphNum], TRUE);
				DrawFormatStringToHandle(60, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], ItemInfoList::GetItemInfoList()[tempItemList[i].first].name.c_str());

				DrawFormatStringToHandle(200, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥%d", ItemInfoList::GetItemInfoList()[tempItemList[i].first].sellMoney);

				if (playerData->GetPlayerStatus()->GetHoldItemList()[tempItemList[i].first] == ItemInfoList::GetItemInfoList()[tempItemList[i].first].maxHoldNum)
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[tempItemList[i].first]);
				}
				else
				{
					DrawFormatStringToHandle(330, 30 + itemGapLengthY*(i - offset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持数：%d", playerData->GetPlayerStatus()->GetHoldItemList()[tempItemList[i].first]);
				}
				Function::Alpha(255);
			}
		}
		if (offset > 0)
		{
			DrawRotaGraph(205, 20, 0.7, M_PI, cursor, TRUE);
		}
		if (tempItemList.size() - offset >= 16)
		{
			DrawRotaGraph(205, 480, 0.7, 0.0, cursor, TRUE);
		}

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

		DrawFormatStringToHandle(770 - 10 * digits1 - 18, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "￥");
		DrawFormatStringToHandle(770 - 10 * digits1, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "%d", playerData->GetPlayerStatus()->GetMoney());
		DrawFormatStringToHandle(610, 20, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "所持金：");

		DrawFillBox(708, 408, 792, 492, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(710, 410, 790, 490, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

		for (int i = 0; i < 2; i++)
		{
			if (cursorNum3 != i)
			{
				Function::Alpha(128);
			}

			switch (i)
			{
			case 0:
				DrawFormatStringToHandle(725, 425 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "はい");
				break;
			case 1:
				DrawFormatStringToHandle(725, 425 + itemGapLengthY*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "いいえ");
				break;
			}
			Function::Alpha(255);
		}

		DrawFillBox(8, 498, 792, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 500, 790, 590, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		DrawFormatStringToHandle(25, 509, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], "合計￥%dになります。本当に売却しますか？", ItemInfoList::GetItemInfoList()[tempItemList[cursorNum1].first].buyMoney*cursorNum2);
	}
	break;
	}

	if (windowList.size() != 0)
	{
		windowList.back()->Draw();
	}
}