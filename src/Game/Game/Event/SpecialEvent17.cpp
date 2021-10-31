#include"../header/SpecialEvent17.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent17::SpecialEvent17()
{
	playerDirection = Direction::DOWN;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 6 + Define::MASU_SIZE / 2);
	playerMoveTime = 0;
	peopleDirection = Direction::DOWN;
	peoplePosition = Vector2<int>(32 * 13 + Define::MASU_SIZE / 2, 32 * 6 + Define::MASU_SIZE / 2);
	peopleMoveTime = 0;
	bossPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * (-2) + Define::MASU_SIZE / 2);
	darkAlpha = 255;
	shake = Vector2<int>(0, 0);
}

SpecialEvent17::~SpecialEvent17()
{

}

void SpecialEvent17::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (0 <= eventTimer&&eventTimer < 224)
	{
		playerPosition.y++;
		peoplePosition.y++;
		playerMoveTime++;
		peopleMoveTime++;
	}
	if (eventTimer == 224)
	{
		playerMoveTime = 0;
		peopleMoveTime = 0;
	}
	if (176 <= eventTimer&&eventTimer < 224)
	{
		bossPosition.y += 4;
	}
	if (224 <= eventTimer&&eventTimer < 300)
	{
		if (2 <= (eventTimer - 224) % 8 && (eventTimer - 224) % 8 < 6)
		{
			shake.y++;
		}
		else
		{
			shake.y--;
		}
	}
	if (eventTimer == 300)
	{
		shake.y = 0;
		playerDirection = Direction::UP;
		peopleDirection = Direction::UP;
	}
	if (eventTimer == 360)
	{
		vector<string> messages;
		messages.push_back("グオオオオオオオオオオオオオオオオオオオ！");
		windowList.push_back(make_shared<MessageWindow>("", messages));
	}
	if (390 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 490)
	{
		endFlag = true;
	}
}

void SpecialEvent17::Draw()
{
	Vector2<int> offset = Vector2<int>(25, 30);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[64].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[64].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i + shake.y, mapBackChip[MapInfoList::GetMapInfoList()[64].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[64].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[64].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[64].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[64].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[64].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[64].mapObject[1][pos.y][pos.x]], TRUE);
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
		DrawRotaGraph(playerPosition.x, playerPosition.y + shake.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + animationFrame], TRUE);
	}
	{
		int animationFrame;
		if (peopleMoveTime != 0)
		{
			animationFrame = ((peopleMoveTime + 8) / 4) % 3;
		}
		else
		{
			animationFrame = 1;
		}
		DrawRotaGraph(peoplePosition.x, peoplePosition.y + shake.y, 1.0, 0.0, peopleGraph[30][(int)peopleDirection * 3 + animationFrame], TRUE);
	}

	DrawRotaGraph(bossPosition.x, bossPosition.y + shake.y, 1.0, 0.0, bossGraph[3], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}