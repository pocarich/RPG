#include"../header/SpecialEvent07.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent07::SpecialEvent07()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 19 + Define::MASU_SIZE / 2);
	playerMoveTime = 0;
	peopleDirection = Direction::RIGHT;
	peoplePosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 5 + Define::MASU_SIZE / 2);
	peopleMoveTime = 0;
	bossPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * (-3) + Define::MASU_SIZE / 2);
	darkAlpha = 255;
	shake = Vector2<int>(0, 0);
}

SpecialEvent07::~SpecialEvent07()
{

}

void SpecialEvent07::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		vector<string> messages;
		messages.push_back("おお・・・。これは珍しいものだ・・・。");
		messages.push_back("はやく採ってドラゴンに気づかれる前に帰らないと・・・。");
		windowList.push_back(make_shared<MessageWindow>("村人", messages));
	}
	if (130 <= eventTimer&&eventTimer < 210)
	{
		playerPosition.y -= 2;
		playerMoveTime++;
	}
	if (eventTimer == 210)
	{
		playerMoveTime = 0;
	}
	if (eventTimer == 230)
	{
		peopleDirection = Direction::DOWN;
	}
	if (eventTimer == 240)
	{
		vector<string> messages;
		messages.push_back("うわ！誰ですかあなたたちは・・・。");
		messages.push_back("そんなことよりそんなところに突っ立ってるとドラゴンに気づかれて・・・。");
		windowList.push_back(make_shared<MessageWindow>("村人", messages));
	}
	if (eventTimer == 271)
	{
		windowList.push_back(make_shared<MessageWindow>("ドラゴン", "グオオオオオオオオオ"));
	}
	if (eventTimer == 272)
	{
		windowList.push_back(make_shared<MessageWindow>("村人", "ひぃっ!"));
	}
	if (280 <= eventTimer&&eventTimer < 344)
	{
		peoplePosition.y += 4;
		peopleMoveTime++;
	}
	if (eventTimer == 344)
	{
		peopleDirection = Direction::RIGHT;
	}
	if (344 <= eventTimer&&eventTimer < 352)
	{
		peoplePosition.x += 4;
		peopleMoveTime++;
	}
	if (eventTimer == 352)
	{
		peopleDirection = Direction::DOWN;
	}
	if (352 <= eventTimer&&eventTimer < 360)
	{
		peoplePosition.y += 4;
		peopleMoveTime++;
	}
	if (eventTimer == 360)
	{
		peopleDirection = Direction::UP;
		peopleMoveTime = 0;
	}
	if (380 <= eventTimer&&eventTimer < 428)
	{
		bossPosition.y += 8;
	}
	if (430 <= eventTimer&&eventTimer < 490)
	{
		if (2 <= (eventTimer - 430) % 8 && (eventTimer - 430) % 8 < 6)
		{
			shake.y++;
		}
		else
		{
			shake.y--;
		}
	}
	if (eventTimer == 490)
	{
		shake.y = 0;
	}
	if (eventTimer == 520)
	{
		vector<string> messages;
		messages.push_back("やべぇよ・・・やべぇよ・・・。");
		windowList.push_back(make_shared<MessageWindow>("村人", messages));
	}
	if (eventTimer == 530)
	{
		peopleDirection = Direction::LEFT;
	}
	if (eventTimer == 540)
	{
		vector<string> messages;
		messages.push_back("見たところ戦闘には自信がありそうですね。");
		messages.push_back("何とかしてあいつを仕留めてください！");
		windowList.push_back(make_shared<MessageWindow>("村人", messages));
	}
	if (570 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 670)
	{
		endFlag = true;
	}
}

void SpecialEvent07::Draw()
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
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i+shake.y, mapBackChip[MapInfoList::GetMapInfoList()[39].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[39].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[39].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[39].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[39].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[39].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[39].mapObject[1][pos.y][pos.x]], TRUE);
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
		DrawRotaGraph(peoplePosition.x, peoplePosition.y + shake.y, 1.0, 0.0, peopleGraph[1][(int)peopleDirection * 3 + animationFrame], TRUE);
	}

	DrawRotaGraph(bossPosition.x, bossPosition.y + shake.y, 1.0, 0.0, bossGraph[0], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}