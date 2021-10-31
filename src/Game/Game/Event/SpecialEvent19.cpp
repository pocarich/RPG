#include"../header/SpecialEvent19.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent19::SpecialEvent19()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * (-1) + Define::MASU_SIZE / 2);
	playerMoveTime = 0;
	peopleDirection = Direction::UP;
	peoplePosition = Vector2<int>(32 * 13 + Define::MASU_SIZE / 2, 32 * (-1) + Define::MASU_SIZE / 2);
	peopleMoveTime = 0;
	bossPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 4 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
	whiteAlpha = 255;
	circleScale = 0.0;
	shake = Vector2<int>(0, 0);
	camera = Vector2<int>(0, 360);
}

SpecialEvent19::~SpecialEvent19()
{

}

void SpecialEvent19::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (0 <= eventTimer&&eventTimer < 180)
	{
		camera.y -= 2;
	}
	if (eventTimer == 180)
	{
		playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 19 + Define::MASU_SIZE / 2);
		peoplePosition = Vector2<int>(32 * 13 + Define::MASU_SIZE / 2, 32 * 19 + Define::MASU_SIZE / 2);
	}
	if (180 <= eventTimer&&eventTimer < 340)
	{
		playerPosition.y--;
		peoplePosition.y--;
		playerMoveTime++;
		peopleMoveTime++;
	}
	if (eventTimer == 340)
	{
		playerMoveTime = 0;
		peopleMoveTime = 0;
	}
	if (400 <= eventTimer&&eventTimer < 415)
	{
		circleScale += 50;
	}
	if (540 <= eventTimer&&eventTimer < 640)
	{
		whiteAlpha -= 3;
		whiteAlpha = max(whiteAlpha, 0);
	}
	if (eventTimer == 700)
	{
		vector<string> messages;
		messages.push_back("ようやくこの時が来たか。");
		messages.push_back("待ち侘びていたぞ、力ある戦士たちよ。");
		messages.push_back("そなたらは私が課した試練を乗り越えここまでたどり着いた。");
		messages.push_back("そなたらがこうしてこの場にたどり着いてくれたことに感謝を。");
		messages.push_back("そして");
		messages.push_back("$そなたらとこうしてこの場で対峙できることに感謝を！");
		windowList.push_back(make_shared<MessageWindow>("", messages));
	}
	if (700 <= eventTimer&&eventTimer < 940)
	{
		if (2 <= (eventTimer - 700) % 8 && (eventTimer -700) % 8 < 6)
		{
			shake.y++;
		}
		else
		{
			shake.y--;
		}
		if ((eventTimer - 700) % 120 < 60)
		{
			whiteAlpha += 3;
			whiteAlpha = min(whiteAlpha, 255);
		}
		else
		{
			whiteAlpha -= 3;
			whiteAlpha = max(whiteAlpha, 0);
		}
	}
	if (eventTimer == 940)
	{
		shake.y = 0;
		whiteAlpha = 0;
	}
	if (eventTimer == 940)
	{
		vector<string> messages;
		messages.push_back("さぁ、これが最後の試練だ。");
		messages.push_back("そなたらがこれまでに培ってきた力を我に示せ。");
		messages.push_back("そして我が力を超えて見せよ！");
		windowList.push_back(make_shared<MessageWindow>("", messages));
	}
	if (970 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 1070)
	{
		endFlag = true;
	}
}

void SpecialEvent19::Draw()
{
	Vector2<int> offset = Vector2<int>(25, 26);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[92].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[92].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j - camera.x, (float)Define::MASU_SIZE*i - camera.y + shake.y, mapBackChip[MapInfoList::GetMapInfoList()[92].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[92].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[92].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j - camera.x, (float)Define::MASU_SIZE*i - camera.y + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[92].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[92].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[92].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j - camera.x, (float)Define::MASU_SIZE*i - camera.y + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[92].mapObject[1][pos.y][pos.x]], TRUE);
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
		DrawRotaGraph(peoplePosition.x - camera.x, peoplePosition.y - camera.y + shake.y, 1.0, 0.0, peopleGraph[30][(int)peopleDirection * 3 + animationFrame], TRUE);
	}

	if (415 < eventTimer)
	{
		DrawRotaGraph(bossPosition.x - camera.x, bossPosition.y - camera.y + shake.y, 1.0, 0.0, bossGraph[8], TRUE);
	}

	Function::Alpha(whiteAlpha);
	DrawCircle(32 * 12 + Define::MASU_SIZE / 2, 32 * 5 + Define::MASU_SIZE / 2, (int)circleScale, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], TRUE);
	Function::Alpha(255);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}