#include"../header/TalkMgr.h"
#include"../header/PeopleInfoList.h"
#include"../header/MessageWindow.h"

TalkMgr::TalkMgr(int peopleKind, list<WindowPtr>& windowList):peopleKind(peopleKind),windowList(windowList)
{
	endFlag = false;
	state = 0;
}

void TalkMgr::Update()
{
	switch (peopleKind)
	{
	default:
		switch (state)
		{
		case 0:
			windowList.push_back(make_shared<MessageWindow>(PeopleInfoList::GetPeopleInfoList()[peopleKind].name, PeopleInfoList::GetPeopleInfoList()[peopleKind].message));
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