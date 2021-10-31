#include"../header/SpecialEvent00.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent00::SpecialEvent00()
{
	playerDirection = Direction::DOWN;
	playerPosition = Vector2<int>(32 * 7 + Define::MASU_SIZE / 2, 32 * 11 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
}

SpecialEvent00::~SpecialEvent00()
{

}

void SpecialEvent00::UpdateEvent()
{
	if (eventTimer == 0)
	{
		windowList.push_back(make_shared<MessageWindow>("ママ", "クリスー！起きなさーい！"));
	}
	if (0 < eventTimer&&eventTimer < 300)
	{
		darkAlpha--;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 300)
	{
		playerDirection = Direction::RIGHT;
	}
	if (300 <= eventTimer&&eventTimer < 332)
	{
		playerPosition.x++;
	}
	if (400<eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 500)
	{
		endFlag = true;
	}
}

void SpecialEvent00::Draw()
{
	Vector2<int> offset = Vector2<int>(16, 19);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y)&&(pos.y) < MapInfoList::GetMapInfoList()[95].heightNum && 0 <= (pos.x)&&(pos.x) < MapInfoList::GetMapInfoList()[95].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapBackChip[MapInfoList::GetMapInfoList()[95].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[95].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[95].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[95].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[95].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[95].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[95].mapObject[1][pos.y][pos.x]], TRUE);
		}
	}

	DrawRotaGraph(playerPosition.x, playerPosition.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + 1], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}