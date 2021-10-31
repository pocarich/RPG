#include"../header/SpecialEvent12.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent12::SpecialEvent12()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 14 + Define::MASU_SIZE / 2);
	peopleDirection = Direction::UP;
	peoplePosition = Vector2<int>(32 * 11 + Define::MASU_SIZE / 2, 32 * 14 + Define::MASU_SIZE / 2);
	playerMoveTime = 0;
	peopleMoveTime = 0;
	darkAlpha = 255;
}

SpecialEvent12::~SpecialEvent12()
{

}

void SpecialEvent12::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (0 <= eventTimer&&eventTimer < 160)
	{
		playerPosition.y--;
		peoplePosition.y--;
		playerMoveTime++;
		peopleMoveTime++;
	}
	if (eventTimer == 160)
	{
		playerMoveTime = 0;
		peopleMoveTime = 0;
	}
	if (eventTimer == 170)
	{
		vector<string> messages;
		messages.push_back("これがルティラ樹みたいね。");
		messages.push_back("さっそく木材をいただきましょう。");
		windowList.push_back(make_shared<MessageWindow>("アリア", messages));
	}
	if (200 < eventTimer&&eventTimer < 270)
	{
		darkAlpha += 5;
		darkAlpha = min(darkAlpha, 255);
	}
	if (300 < eventTimer&&eventTimer < 370)
	{
		darkAlpha -= 5;
		darkAlpha = max(darkAlpha, 0);
	}
	if (eventTimer == 380)
	{
		vector<string> messages;
		messages.push_back("これだけあればおそらく大丈夫ね。");
		messages.push_back("さあ、急いで村に戻りましょう！");
		windowList.push_back(make_shared<MessageWindow>("アリア", messages));
	}
	if (410 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 510)
	{
		endFlag = true;
	}
}

void SpecialEvent12::Draw()
{
	Vector2<int> offset = Vector2<int>(25, 29);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[50].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[50].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapBackChip[MapInfoList::GetMapInfoList()[50].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[50].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[50].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[50].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[50].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[50].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[50].mapObject[1][pos.y][pos.x]], TRUE);
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
		DrawRotaGraph(playerPosition.x, playerPosition.y , 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + animationFrame], TRUE);
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
		DrawRotaGraph(peoplePosition.x, peoplePosition.y , 1.0, 0.0, peopleGraph[30][(int)peopleDirection * 3 + animationFrame], TRUE);
	}

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}