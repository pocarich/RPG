#include"../header/SpecialEvent.h"
#include"../header/Function.h"

GHandle SpecialEvent::mapBackChip[20 * 30];
GHandle SpecialEvent::mapObjectChip[20 * 20];
GHandle SpecialEvent::bossGraph[Define::BOSS_KIND_NUM];
GHandle SpecialEvent::peopleGraph[Define::PEOPLE_KIND_MAX][(int)Direction::SIZE * 3];
GHandle SpecialEvent::playerGraph[Define::CHARACTER_NUM][(int)Direction::SIZE * 3];

SpecialEvent::SpecialEvent()
{
	eventTimer = 0;
	endFlag = false;
}

SpecialEvent::~SpecialEvent()
{

}

void SpecialEvent::Load()
{
	int result = LoadDivGraph("data/graph/map/objectChip.png", 400, 20, 20, 32, 32, mapObjectChip);

	assert(result == 0 && "SpecialEvent::Load()‚É‚Ä‰æ‘œ‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½B");

	result = LoadDivGraph("data/graph/map/haikeiChip.png", 600, 20, 30, 32, 32, mapBackChip);

	assert(result == 0 && "SpecialEvent::Load()‚É‚Ä‰æ‘œ‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½B");

	for (int i = 0; i < Define::PEOPLE_KIND_MAX; i++)
	{
		stringstream ss;
		ss << "data/graph/character/people/people" << Function::NumToStringFillZero(i, 2) << ".png";
		result = LoadDivGraph(ss.str().c_str(), 12, 3, (int)Direction::SIZE, 32, 32, peopleGraph[i]);

		assert(result == 0 && "SpecialEvent::Load()‚É‚Ä‰æ‘œ‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½B");
	}

	for (int i = 0; i < Define::CHARACTER_NUM; i++)
	{
		stringstream ss;
		ss << "data/graph/character/player/player" << i << ".png";
		result = LoadDivGraph(ss.str().c_str(), 12, 3, (int)Direction::SIZE, 32, 32, playerGraph[i]);
		assert(result == 0 && "SpecialEvent::Load()‚É‚Ä‰æ‘œ‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½B");
	}

	for (int i = 0; i < Define::BOSS_KIND_NUM; i++)
	{
		stringstream ss;
		ss << "data/graph/character/enemy/boss" << Function::NumToStringFillZero(i, 3) << ".png";
		bossGraph[i] = LoadGraph(ss.str().c_str());
		assert(bossGraph[i] != 0 && "BossMap::Load()‚É‚Ä¸”s‚µ‚Ü‚µ‚½B");
	}
}

void SpecialEvent::UpdateEventTimer()
{
	eventTimer++;
}

void SpecialEvent::Update()
{
	if (windowList.size() != 0)
	{
		UpdateWindow();
	}
	else
	{
		UpdateEvent();
		UpdateEventTimer();
	}
}

void SpecialEvent::UpdateWindow()
{
	windowList.back()->Update();

	auto itr = remove_if(windowList.begin(), windowList.end(), [](WindowPtr& obj)
	{
		return obj->GetEndFlag();
	});
	windowList.erase(itr, windowList.end());
}