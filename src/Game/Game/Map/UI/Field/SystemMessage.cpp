#include"../header/SystemMessage.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Function.h"

SystemMessage::SystemMessage()
{

}

SystemMessage::~SystemMessage()
{

}

void SystemMessage::Update()
{
	if (messageList.size() == 0)
	{
		return;
	}

	for (auto& n : timer)
	{
		n--;
		n = max(0, n);
	}

	if (timer.front() == 0)
	{
		timer.erase(timer.begin());
		messageList.erase(messageList.begin());
	}
}

void SystemMessage::Draw()
{
	if (messageList.size() == 0)
	{
		return;
	}

	Function::Alpha(128);
	DrawFillBox(7, 7, 300, 10 + 20 * messageList.size(), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	static const int gapLength = 20;
	for (int i = 0; i != messageList.size(); i++)
	{
		DrawFormatStringToHandle(10, 10 + gapLength*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[10], messageList[i].c_str());
	}
}

void SystemMessage::AddMessage(string message)
{
	messageList.push_back(message);
	timer.push_back(180);
}