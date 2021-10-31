#include"../header/EventMgr.h"
#include"../header/EventInfoList.h"
#include"../header/MessageWindow.h"

EventMgr::EventMgr(int eventKind, list<WindowPtr>& windowList) :eventKind(eventKind), windowList(windowList)
{
	endFlag = false;
	state = 0;
}

void EventMgr::Update()
{
	switch (eventKind)
	{
	default:
		switch (state)
		{
		case 0:
			windowList.push_back(make_shared<MessageWindow>("", EventInfoList::GetEventInfoList()[eventKind].messages));
			state++;
			break;
		case 1:
			if (windowList.back()->GetEndFlag())
			{
				windowList.clear();
				endFlag = true;
			}
			break;
		}
		break;
	}
}