#include"../header/SelectWindow.h"
#include"../header/KeyBoard.h"
#include"../header/ColorMgr.h"
#include"../header/FontMgr.h"
#include"../header/SEMgr.h"

const char alphabet[27] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

SelectWindow::SelectWindow(Type type_, int dataNum_, string name_) :type(type_), dataNum(dataNum_)
{
	for (int i = 0; i < dataNum; i++)dataList.push_back(0);
	
	koumokuNum = 0;
	if (type == Type::NORMAL)
	{
		string name = name_;
		int point = 0;
		int counter = 0;

		while (point + counter != name.size())
		{
			if (name[point + counter] == '/')
			{
				string str;
				str = name.substr(point, counter);
				nameList.push_back(str);
				point = point + counter + 1;
				counter = 0;
				koumokuNum++;
			}
			counter++;
		}
		string str;
		str = name.substr(point, counter);
		nameList.push_back(str);
		koumokuNum++;
	}
	dataPoint = 0;

	windowLength = 0;
	windowHeight = 0;

	int length = 0;
	switch (type)
	{
	case Type::NORMAL:
		for (int i = 0; i != nameList.size(); i++)
		{
			if (length < nameList[i].size())length = nameList[i].size();
		}

		windowLength = length / 2 * 20 + 20;
		windowHeight = 25 * koumokuNum + 20;
		break;
	case Type::NUM:
		windowLength = dataNum * 20 + 20;
		windowHeight = 20 + 20;
		break;
	case Type::ALPHABET:
		windowLength = dataNum * 20 + 20;
		windowHeight = 20 + 20;
		break;
	}
}

void SelectWindow::Update()
{
	if (KeyBoard::PushOnce(KEY_INPUT_Z))
	{
		switch (type)
		{
		case Type::NORMAL:
			if (dataList[0] % 2 == 0)
			{
				SEMgr::UpdateFlag(0);
			}
			else
			{
				SEMgr::UpdateFlag(1);
			}
			break;
		default:
			SEMgr::UpdateFlag(0);
			break;
		}
		endFlag = true;
	}
	Change();
}

void SelectWindow::Change()
{
	switch (type)
	{
	case Type::NORMAL:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))dataList[0] = (dataList[0] + 1) % koumokuNum;
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))dataList[0] = (dataList[0] + koumokuNum - 1) % koumokuNum;
		break;
	case Type::NUM:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))dataList[dataPoint] = (dataList[dataPoint] + 1) % 10;
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))dataList[dataPoint] = (dataList[dataPoint] + 9) % 10;
		if (KeyBoard::PushOnce(KEY_INPUT_RIGHT))dataPoint = (dataPoint + 1) % dataNum;
		if (KeyBoard::PushOnce(KEY_INPUT_LEFT))dataPoint = (dataPoint + dataNum-1) % dataNum;
		break;
	case Type::ALPHABET:
		if (KeyBoard::PushOnce(KEY_INPUT_UP))dataList[dataPoint] = (dataList[dataPoint] + 1) % 26;
		if (KeyBoard::PushOnce(KEY_INPUT_DOWN))dataList[dataPoint] = (dataList[dataPoint] + 25) % 26;
		if (KeyBoard::PushOnce(KEY_INPUT_RIGHT))dataPoint = (dataPoint + 1) % dataNum;
		if (KeyBoard::PushOnce(KEY_INPUT_LEFT))dataPoint = (dataPoint + dataNum - 1) % dataNum;
		break;
	}
}

void SelectWindow::Draw()
{
	switch (type)
	{
	case Type::NORMAL:
		DrawFillBox(WINDOW_BASE_X - windowLength-2, WINDOW_BASE_Y - windowHeight-2, WINDOW_BASE_X+2, WINDOW_BASE_Y+2, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(WINDOW_BASE_X - windowLength, WINDOW_BASE_Y - windowHeight, WINDOW_BASE_X, WINDOW_BASE_Y, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		for (int i = 0; i != koumokuNum; i++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, i == dataList[0]? 255 : 128);
			DrawFormatStringToHandle(WINDOW_BASE_X - windowLength + 10, WINDOW_BASE_Y - windowHeight + 10 + 25 * i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], "%s", nameList[i].c_str());
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		break;
	case Type::NUM:
		for (int i = 0; i != dataNum; i++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, i == dataPoint? 255 : 128);
			DrawFormatStringToHandle(WINDOW_BASE_X - windowLength + 10 + 20 * i, WINDOW_BASE_Y - windowHeight + 10, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], "%d", dataList[i] % 10);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		break;
	case Type::ALPHABET:
		for (int i = 0; i != dataNum; i++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, i == dataPoint? 255 : 128);
			DrawFormatStringToHandle(WINDOW_BASE_X - windowLength + 10 + 20 * i, WINDOW_BASE_Y - windowHeight + 10, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[12], "%c", alphabet[dataList[i] % 26]);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		break;
	}
}