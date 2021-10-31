#include"../header/MessageWindow.h"
#include"../header/ColorMgr.h"
#include"../header/FontMgr.h"
#include"../header/KeyBoard.h"
#include"../header/Function.h"
#include"../header/SEMgr.h"

MessageWindow::MessageWindow(string name, vector<string> messageList)
{
	charNum = 0;
	strNum = 0;
	pushEnterFlag = false;
	timer = 0;
	delayTimer = 0;
	dispName = true;

	this->name = name;
	this->messageList = messageList;

	while (true)
	{
		if (messageList[min(strNum, messageList.size() - 1)][0] == '$')
		{
			delayTimer = DELAY_TIME;
			messageList[min(strNum, messageList.size() - 1)].erase(messageList[min(strNum, messageList.size() - 1)].begin());
		}
		else if (messageList[min(strNum, messageList.size() - 1)][0] == '%')
		{
			dispName = false;
			messageList[min(strNum, messageList.size() - 1)].erase(messageList[min(strNum, messageList.size() - 1)].begin());
		}
		else
		{
			break;
		}
	}
}

MessageWindow::MessageWindow(string name, string message)
{
	charNum = 0;
	strNum = 0;
	pushEnterFlag = false;
	timer = 0;
	delayTimer = 0;
	dispName = true;

	this->name = name;
	this->messageList.push_back(message);

	while (true)
	{
		if (messageList[min(strNum, messageList.size() - 1)][0] == '$')
		{
			delayTimer = DELAY_TIME;
			messageList[min(strNum, messageList.size() - 1)].erase(messageList[min(strNum, messageList.size() - 1)].begin());
		}
		else if (messageList[min(strNum, messageList.size() - 1)][0] == '%')
		{
			dispName = false;
			messageList[min(strNum, messageList.size() - 1)].erase(messageList[min(strNum, messageList.size() - 1)].begin());
		}
		else
		{
			break;
		}
	}
}

void MessageWindow::Update()
{
	UpdateMessage();
	UpdateTimer();
}

void MessageWindow::UpdateMessage()
{
	if (delayTimer != 0)
	{
		delayTimer--;
	}
	else
	{
		if (timer%NEXT_MOJI_TIME == 0 && !pushEnterFlag)
		{
			charNum += 2;
			charNum = min(charNum, messageList[strNum].size());
		}
		if (charNum == messageList[strNum].size())
		{
			pushEnterFlag = true;
		}
		if (pushEnterFlag)if (KeyBoard::PushOnce(KEY_INPUT_Z))
		{
			if (strNum == messageList.size() - 1)
				endFlag = true;
			else
			{
				SEMgr::UpdateFlag(0);
				charNum = 0;
				strNum++;
				dispName = true;
				while (true)
				{
					if (messageList[min(strNum, messageList.size() - 1)][0] == '$')
					{
						delayTimer = DELAY_TIME;
						messageList[min(strNum, messageList.size() - 1)].erase(messageList[min(strNum, messageList.size() - 1)].begin());
					}
					else if (messageList[min(strNum, messageList.size() - 1)][0] == '%')
					{
						dispName = false;
						messageList[min(strNum, messageList.size() - 1)].erase(messageList[min(strNum, messageList.size() - 1)].begin());
					}
					else
					{
						break;
					}
				}
			}
			pushEnterFlag = false;
		}
	}
}

void MessageWindow::UpdateTimer()
{
	timer++;
}

void MessageWindow::Draw()
{
	if (delayTimer == 0)
	{
		if (name != ""&&dispName)
		{
			DrawFillBox(8, 470, 132, 504, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
			DrawFillBox(10, 472, 130, 502, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		}
		DrawFillBox(8, 510, 792, 592, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
		DrawFillBox(10, 512, 790, 590, ColorMgr::GetColorCode()[(int)ColorMgr::CustomColor::COLOR1]);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		if (dispName)
		{
			DrawFormatStringToHandle(Function::CalcCenterOfString(10, 130, FontMgr::GetFont()[11], name.c_str()), 477, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], name.c_str());
		}

		char buf[3];
		for (int i = 0, counter = 0; i < charNum;)
		{
			if (messageList[min(strNum, messageList.size() - 1)][i] == '/')
			{
				counter += MOJI_MAX_X;
				counter -= counter%MOJI_MAX_X;
				i++;
				continue;
			}
			buf[0] = messageList[min(strNum, messageList.size() - 1)][i];
			buf[1] = messageList[min(strNum, messageList.size() - 1)][i + 1];
			buf[2] = '\0';
			DrawFormatStringToHandle(20 + 20 * (counter % MOJI_MAX_X), -15 * max(0, (((charNum / 2) / MOJI_MAX_X) - 2)) + 521 + 20 * (counter / MOJI_MAX_X), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[11], buf);
			i += 2;
			counter++;
		}
	}
}