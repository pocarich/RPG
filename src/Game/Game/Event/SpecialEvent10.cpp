#include"../header/SpecialEvent10.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent10::SpecialEvent10()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 19 + Define::MASU_SIZE / 2);
	playerMoveTime = 0;
	peopleDirection = Direction::UP;
	peoplePosition = Vector2<int>(32 * 11 + Define::MASU_SIZE / 2, 32 * 19 + Define::MASU_SIZE / 2);
	peopleMoveTime = 0;
	bossPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * (-2) + Define::MASU_SIZE / 2);
	darkAlpha = 255;
	shake = Vector2<int>(0, 0);
}

SpecialEvent10::~SpecialEvent10()
{

}

void SpecialEvent10::UpdateEvent()
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
		messages.push_back("だいぶ奥まったところまできたわね。");
		messages.push_back("ルティラ樹までもう少しってところかしら。");
		windowList.push_back(make_shared<MessageWindow>("アリア", messages));
	}
	if (240 <= eventTimer&&eventTimer < 300)
	{
		if (2 <= (eventTimer - 240) % 8 && (eventTimer - 240) % 8 < 6)
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
	}

	if (360 <= eventTimer&&eventTimer < 420)
	{
		if (2 <= (eventTimer - 360) % 8 && (eventTimer - 360) % 8 < 6)
		{
			shake.y++;
		}
		else
		{
			shake.y--;
		}
	}
	if (eventTimer == 420)
	{
		shake.y = 0;
	}
	if (eventTimer == 480)
	{
		windowList.push_back(make_shared<MessageWindow>("アリア", "何かしら、この振動・・・？"));
	}
	if (500 <= eventTimer&&eventTimer < 532)
	{
		bossPosition.y++;
	}
	if (532 <= eventTimer&&eventTimer < 592)
	{
		if (2 <= (eventTimer - 532) % 8 && (eventTimer - 532) % 8 < 6)
		{
			shake.y++;
		}
		else
		{
			shake.y--;
		}
	}
	if (eventTimer == 592)
	{
		shake.y = 0;
	}
	if (600 <= eventTimer&&eventTimer < 632)
	{
		bossPosition.y++;
	}
	if (632 <= eventTimer&&eventTimer < 692)
	{
		if (2 <= (eventTimer - 632) % 8 && (eventTimer - 632) % 8 < 6)
		{
			shake.y++;
		}
		else
		{
			shake.y--;
		}
	}
	if (eventTimer == 692)
	{
		shake.y = 0;
	}
	if (700 <= eventTimer&&eventTimer < 732)
	{
		bossPosition.y++;
	}
	if (732 <= eventTimer&&eventTimer < 792)
	{
		if (2 <= (eventTimer - 732) % 8 && (eventTimer - 732) % 8 < 6)
		{
			shake.y++;
		}
		else
		{
			shake.y--;
		}
	}
	if (eventTimer == 792)
	{
		shake.y = 0;
	}
	if (800 <= eventTimer&&eventTimer < 832)
	{
		bossPosition.y++;
	}
	if (832 <= eventTimer&&eventTimer < 892)
	{
		if (2 <= (eventTimer - 832) % 8 && (eventTimer - 832) % 8 < 6)
		{
			shake.y++;
		}
		else
		{
			shake.y--;
		}
	}
	if (eventTimer == 892)
	{
		shake.y = 0;
	}
	if (900 <= eventTimer&&eventTimer < 932)
	{
		bossPosition.y++;
	}
	if (932 <= eventTimer&&eventTimer < 992)
	{
		if (2 <= (eventTimer - 932) % 8 && (eventTimer - 932) % 8 < 6)
		{
			shake.y++;
		}
		else
		{
			shake.y--;
		}
	}
	if (eventTimer == 992)
	{
		shake.y = 0;
	}
	if (1000 <= eventTimer&&eventTimer < 1032)
	{
		bossPosition.y++;
	}
	if (1032 <= eventTimer&&eventTimer < 1092)
	{
		if (2 <= (eventTimer - 1032) % 8 && (eventTimer - 1032) % 8 < 6)
		{
			shake.y++;
		}
		else
		{
			shake.y--;
		}
	}
	if (eventTimer == 1092)
	{
		shake.y = 0;
	}
	if (eventTimer == 1100)
	{
		vector<string> messages;
		messages.push_back("ちょっと、こんな魔物がいるなんて聞いてないわよ！");
		messages.push_back("簡単にはルティラ樹の元まではたどり着けないってわけね・・・。");
		messages.push_back("とにかく何とかしてやっつけちゃいましょう！");
		windowList.push_back(make_shared<MessageWindow>("アリア", messages));
	}
	if (1130 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 1230)
	{
		endFlag = true;
	}
}

void SpecialEvent10::Draw()
{
	Vector2<int> offset = Vector2<int>(25, 28);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[49].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[49].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i + shake.y, mapBackChip[MapInfoList::GetMapInfoList()[49].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[49].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[49].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[49].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[49].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[49].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[49].mapObject[1][pos.y][pos.x]], TRUE);
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

	DrawRotaGraph(bossPosition.x, bossPosition.y + shake.y, 1.0, 0.0, bossGraph[1], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}