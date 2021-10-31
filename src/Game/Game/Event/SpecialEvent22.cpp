#include"../header/SpecialEvent22.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent22::SpecialEvent22()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 10 + Define::MASU_SIZE / 2);
	wallPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 3 + Define::MASU_SIZE / 2);
	stonePosition = Vector2<int>(32 * 9 + Define::MASU_SIZE / 2, 32 * 4 + Define::MASU_SIZE / 2);
	playerMoveTime = 0;
	darkAlpha = 255;
	whiteAlpha = 0;
	shake = Vector2<int>(0, 0);
	camera = Vector2<int>(0, 0);
}

SpecialEvent22::~SpecialEvent22()
{

}

void SpecialEvent22::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (150 <= eventTimer&&eventTimer < 182)
	{
		playerPosition.y--;
		playerMoveTime++;
	}
	if (eventTimer == 182)
	{
		playerMoveTime = 0;
	}
	if (210 < eventTimer&&eventTimer < 390)
	{
		whiteAlpha += 2;
		whiteAlpha = min(whiteAlpha, 255);
	}
	if (470 < eventTimer&&eventTimer < 650)
	{
		whiteAlpha -= 2;
		whiteAlpha = max(whiteAlpha, 0);
	}
	if (710 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 810)
	{
		endFlag = true;
	}
}

void SpecialEvent22::Draw()
{
	Vector2<int> offset = Vector2<int>(21, 26);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[7].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[7].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j - camera.x, (float)Define::MASU_SIZE*i - camera.y + shake.y, mapBackChip[MapInfoList::GetMapInfoList()[7].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[7].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[7].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j - camera.x, (float)Define::MASU_SIZE*i - camera.y + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[7].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[7].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[7].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j - camera.x, (float)Define::MASU_SIZE*i - camera.y + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[7].mapObject[1][pos.y][pos.x]], TRUE);
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
		DrawRotaGraph(playerPosition.x - camera.x, playerPosition.y - camera.y + shake.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + animationFrame], TRUE);
	}

	if (eventTimer < 420)
	{
		DrawRotaGraph(wallPosition.x - camera.x, wallPosition.y - camera.y + shake.y, 1.0, 0.0, mapBackChip[3 * 20 + 1], TRUE);
	}
	DrawRotaGraph(stonePosition.x - camera.x, stonePosition.y - camera.y + shake.y, 1.0, 0.0, mapObjectChip[18 * 20 + 1], TRUE);
	DrawRotaGraph(stonePosition.x - camera.x, stonePosition.y - Define::MASU_SIZE - camera.y + shake.y, 1.0, 0.0, mapObjectChip[17 * 20 + 1], TRUE);

	Function::Alpha(whiteAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE]);
	Function::Alpha(255);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}