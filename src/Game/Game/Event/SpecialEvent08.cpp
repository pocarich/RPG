#include"../header/SpecialEvent08.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent08::SpecialEvent08()
{
	playerDirection = Direction::LEFT;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	peopleDirection = Direction::RIGHT;
	peoplePosition = Vector2<int>(32 * 11 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
}

SpecialEvent08::~SpecialEvent08()
{

}

void SpecialEvent08::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		vector<string> messages;
		messages.push_back("���₠�A�ꎞ�͂ǂ��Ȃ邩�Ǝv���܂������f���炵���r�O�ł����ˁB�䌩���ꂢ�����܂����B");
		messages.push_back("���������΂��Ȃ������͂��������ǂ̂悤�Ȃ��p���ł����ɁE�E�E�B");
		windowList.push_back(make_shared<MessageWindow>("���l", messages));
	}
	if (eventTimer == 160)
	{
		vector<string> messages;
		messages.push_back("�Ȃ�ƁA�����z�΍̏W�ɋ΂���ł���ԂɊO�ł���Ȃ��Ƃ��E�E�E�B");
		messages.push_back("���m�������܂����B�������ɃJ���G�b�g���ւƌ������܂��B���Ȃ������͌ォ��������Ƃ��炵�Ă��������B");
		windowList.push_back(make_shared<MessageWindow>("���l", messages));
	}
	if (190 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 290)
	{
		endFlag = true;
	}
}

void SpecialEvent08::Draw()
{
	Vector2<int> offset = Vector2<int>(26, 39);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[39].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[39].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapBackChip[MapInfoList::GetMapInfoList()[39].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[39].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[39].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[39].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[39].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[39].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[39].mapObject[1][pos.y][pos.x]], TRUE);
		}
	}

	DrawRotaGraph(playerPosition.x, playerPosition.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + 1], TRUE);
	DrawRotaGraph(peoplePosition.x, peoplePosition.y, 1.0, 0.0, peopleGraph[1][(int)peopleDirection * 3 + 1], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}