#include"../header/Title.h"
#include"../header/KeyBoard.h"
#include"../header/BGMMgr.h"
#include"../header/SEMgr.h"
#include"../header/Function.h"
#include"../header/MapInfoList.h"
#include"../header/TitleMapInfo.h"
#include"../header/Function.h"

GHandle Title::mapBackChip[20 * 30];
GHandle Title::mapObjectChip[20 * 20];

Title::Title(array<SaveData, Define::SAVE_DATA_NUM>& saveDataList) :saveDataList(saveDataList)
{
	stateEndFlag = false;
	pushStartFlag = false;
	backFlag = false;
	timer = 0;
	darkAlpha = 0;
	loadDataNum = -1;
	state = 1;
	cursorNum1 = 0;
	cursorNum2 = 0;
	camera = Vector2<int>(0, -Define::MASU_SIZE * 40);
}

Title::~Title()
{
	
}

void Title::Load()
{
	int result = LoadDivGraph("data/graph/map/objectChip.png", 400, 20, 20, 32, 32, mapObjectChip);

	assert(result == 0 && "MapField::Load()にて画像の読み込みに失敗しました。");

	result = LoadDivGraph("data/graph/map/haikeiChip.png", 600, 20, 30, 32, 32, mapBackChip);

	assert(result == 0 && "MapField::Load()にて画像の読み込みに失敗しました。");
}

void Title::Main()
{
	Update();
	Draw();
}

void Title::Update()
{
	switch (state)
	{
	case 0:
		camera.y += 1;
		if (camera.y == Define::MASU_SIZE * 20)
		{
			camera.y = -Define::MASU_SIZE * 40;
		}
		
		if (!pushStartFlag)
		{
			if (KeyBoard::PushOnce(KEY_INPUT_Z))
			{
				pushStartFlag = true;
			}
		}
		else
		{
			timer++;
			if (timer == 60)
			{
				state++;
				timer = 0;
				pushStartFlag = false;
			}
		}
		break;
	case 1:
		camera.y += 1;
		if (camera.y == Define::MASU_SIZE * 20)
		{
			camera.y = -Define::MASU_SIZE * 40;
		}
		if (!pushStartFlag)
		{
			if (KeyBoard::PushOnce(KEY_INPUT_Z))
			{
				pushStartFlag = true;
			}
			if (KeyBoard::PushOnce(KEY_INPUT_UP))
			{
				cursorNum1 = 0;
			}
			if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
			{
				cursorNum1 = 1;
			}
		}
		else
		{
			timer++;
			if (cursorNum1 == 0)
			{
				darkAlpha += 3;
				darkAlpha = min(darkAlpha, 255);
				if (timer == 120)
				{
					stateEndFlag = true;
				}
			}
			else
			{
				darkAlpha += 3;
				darkAlpha = min(darkAlpha, 255);
				if (timer == 120)
				{
					state++;
					timer = 0;
					pushStartFlag = false;
					cursorNum1 = 0;
					darkAlpha = 0;
				}
			}
		}
		break;
	case 2:
		if (!pushStartFlag)
		{
			if (KeyBoard::PushOnce(KEY_INPUT_Z))
			{
				if (saveDataList[cursorNum2].exist)
				{
					pushStartFlag = true;
					loadDataNum = cursorNum2;
				}
			}
			if (KeyBoard::PushOnce(KEY_INPUT_X))
			{
				pushStartFlag = true;
				backFlag = true;
			}
			if (KeyBoard::PushOnce(KEY_INPUT_UP))
			{
				cursorNum2--;
				cursorNum2 = max(cursorNum2, 0);
			}
			if (KeyBoard::PushOnce(KEY_INPUT_DOWN))
			{
				cursorNum2++;
				cursorNum2 = min(cursorNum2, Define::SAVE_DATA_NUM - 1);
			}
		}
		else
		{
			timer++;
			if (backFlag)
			{
				darkAlpha += 3;
				darkAlpha = min(darkAlpha, 255);
				if (timer == 120)
				{
					state = 1;
					timer = 0;
					pushStartFlag = false;
					backFlag = false;
					darkAlpha = 0;
				}
			}
			else
			{
				darkAlpha += 3;
				darkAlpha = min(darkAlpha, 255);
				if (timer == 120)
				{
					stateEndFlag = true;
				}
			}
		}
		break;
	}
}

void Title::Draw()
{
	switch (state)
	{
	case 0:
		for (int i = 0; i < 60; i++)for (int j = 0; j < Define::WINDOW_WIDTH / Define::MASU_SIZE; j++)
		{
			DrawGraph(Define::MASU_SIZE*j, Define::MASU_SIZE*i + camera.y, mapBackChip[TitleMapInfo::mapChip[i][j]], TRUE);
		}

		for (int i = 0; i < 60; i++)for (int j = 0; j < Define::WINDOW_WIDTH / Define::MASU_SIZE; j++)
		{
			DrawGraph(Define::MASU_SIZE*j, Define::MASU_SIZE*i + camera.y, mapObjectChip[TitleMapInfo::mapObject[i][j]], TRUE);
		}

		for (int i = 0; i < 60; i++)for (int j = 0; j < Define::WINDOW_WIDTH / Define::MASU_SIZE; j++)
		{
			DrawGraph(Define::MASU_SIZE*j, Define::MASU_SIZE*i + camera.y - Define::MASU_SIZE * 60, mapBackChip[TitleMapInfo::mapChip[i][j]], TRUE);
		}

		for (int i = 0; i < 60; i++)for (int j = 0; j < Define::WINDOW_WIDTH / Define::MASU_SIZE; j++)
		{
			DrawGraph(Define::MASU_SIZE*j, Define::MASU_SIZE*i + camera.y - Define::MASU_SIZE * 60, mapObjectChip[TitleMapInfo::mapObject[i][j]], TRUE);
		}
		DrawFormatStringToHandle(350, 180, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[7], "RPG");
		if ((timer / 5) % 2 == 0)
		{
			DrawFormatStringToHandle(280, 470, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[4], "push 'Z' to start");
		}
		break;
	case 1:
		for (int i = 0; i < 60; i++)for (int j = 0; j < Define::WINDOW_WIDTH / Define::MASU_SIZE; j++)
		{
			DrawGraph(Define::MASU_SIZE*j, Define::MASU_SIZE*i + camera.y, mapBackChip[TitleMapInfo::mapChip[i][j]], TRUE);
		}

		for (int i = 0; i < 60; i++)for (int j = 0; j < Define::WINDOW_WIDTH / Define::MASU_SIZE; j++)
		{
			DrawGraph(Define::MASU_SIZE*j, Define::MASU_SIZE*i + camera.y, mapObjectChip[TitleMapInfo::mapObject[i][j]], TRUE);
		}

		for (int i = 0; i < 60; i++)for (int j = 0; j < Define::WINDOW_WIDTH / Define::MASU_SIZE; j++)
		{
			DrawGraph(Define::MASU_SIZE*j, Define::MASU_SIZE*i + camera.y - Define::MASU_SIZE * 60, mapBackChip[TitleMapInfo::mapChip[i][j]], TRUE);
		}

		for (int i = 0; i < 60; i++)for (int j = 0; j < Define::WINDOW_WIDTH / Define::MASU_SIZE; j++)
		{
			DrawGraph(Define::MASU_SIZE*j, Define::MASU_SIZE*i + camera.y - Define::MASU_SIZE * 60, mapObjectChip[TitleMapInfo::mapObject[i][j]], TRUE);
		}
		DrawFormatStringToHandle(350, 180, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[7], "RPG");
		if ((timer / 5) % 2 == 0 || cursorNum1 != 0)
		{
			if (cursorNum1 != 0)
			{
				Function::Alpha(128);
			}
			DrawFormatStringToHandle(Function::CalcCenterOfString(0,Define::WINDOW_WIDTH, FontMgr::GetFont()[13], "NEW GAME"), 450, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[13], "NEW GAME");
			Function::Alpha(255);
		}
		if ((timer / 5) % 2 == 0 || cursorNum1 != 1)
		{
			if (cursorNum1 != 1)
			{
				Function::Alpha(128);
			}
			DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[13], "LOAD GAME"), 500, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[13], "LOAD GAME");
			Function::Alpha(255);
		}
		break;
	case 2:
		for (int i = 0; i < 12; i++)
		{
			if (i != cursorNum2)
			{
				Function::Alpha(128);
			}

			int offset = 50;
			DrawFillBox(5, 5 + offset*i, Define::WINDOW_WIDTH - 5, 45 + offset*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
			DrawFillBox(7, 7 + offset*i, Define::WINDOW_WIDTH - 7, 43 + offset*i, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);

			DrawFormatStringToHandle(15, 15 + offset*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "データ%02d", i + 1);

			if (saveDataList[i].exist)
			{
				if (saveDataList[i].existCharacterFlag[0])
				{
					DrawFormatStringToHandle(115, 15+offset*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "クリス Lv %d", saveDataList[i].Lv[0]);
				}
				if (saveDataList[i].existCharacterFlag[1])
				{
					DrawFormatStringToHandle(250, 15 + offset*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "アリア Lv %d", saveDataList[i].Lv[1]);
				}
				DrawFormatStringToHandle(400, 15 + offset*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "場所 %s", MapInfoList::GetMapInfoList()[saveDataList[i].mapNum].name.c_str());

				int hour, minute, second;
				int time = saveDataList[i].playTime;
				time /= 60;
				second = time % 60;
				time /= 60;
				minute = time % 60;
				time /= 60;
				hour = time % 60;

				int x = 780 - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[11], "プレイ時間 %02d:%02d:%02d", hour, minute, second);
				DrawFormatStringToHandle(x, 15 + offset*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "プレイ時間 %02d:%02d:%02d", hour, minute, second);
			}
			else
			{
				DrawFormatStringToHandle(400, 15 + offset*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], "新規データ");
			}

			Function::Alpha(255);
		}
		break;
	}

	Function::Alpha(darkAlpha);

	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);

	Function::Alpha(255);
}
