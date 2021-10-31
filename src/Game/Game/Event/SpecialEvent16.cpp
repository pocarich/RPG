#include"../header/SpecialEvent16.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent16::SpecialEvent16()
{
	playerDirection = Direction::LEFT;
	playerPosition = Vector2<int>(32 * 13 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	stonePosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	playerMoveTime = 0;
	darkAlpha = 255;
	shake = Vector2<int>(0, 0);
}

SpecialEvent16::~SpecialEvent16()
{

}

void SpecialEvent16::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		vector<string> messages;
		messages.push_back("êŒîËÇÃâ∫Ç…âΩÇ©Ç™å©Ç¶ÇÈÅB");
		windowList.push_back(make_shared<MessageWindow>("", messages));
	}
	if (130 <= eventTimer&&eventTimer < 162)
	{
		stonePosition.x--;
	}
	if (230 < eventTimer&&eventTimer<330)
	{
		darkAlpha += 5;
		darkAlpha = min(darkAlpha, 255);
	}
	if (eventTimer == 330)
	{
		endFlag = true;
	}
}

void SpecialEvent16::Draw()
{
	Vector2<int> offset = Vector2<int>(7, 1);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j + shake.x, (float)Define::MASU_SIZE*i + shake.y, mapBackChip[MapInfoList::GetMapInfoList()[15].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j + shake.x, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[15].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j + shake.x, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[15].mapObject[1][pos.y][pos.x]], TRUE);
		}
	}

	{
		int animationFrame;
		if (playerMoveTime != 0)
		{
			animationFrame = ((playerMoveTime + 8) / 4) % 3;
		}
		else
		{
			animationFrame = 1;
		}
		DrawRotaGraph(playerPosition.x + shake.x, playerPosition.y + shake.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + animationFrame], TRUE);
	}

	DrawRotaGraph(stonePosition.x + shake.x, stonePosition.y - Define::MASU_SIZE + shake.y, 1.0, 0.0, mapObjectChip[17 * 20 + 1], TRUE);
	DrawRotaGraph(stonePosition.x + shake.x, stonePosition.y + shake.y, 1.0, 0.0, mapObjectChip[18 * 20 + 1], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}