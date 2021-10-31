#include"../header/SpecialEvent03.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent03::SpecialEvent03()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 10 + Define::MASU_SIZE / 2);
	peopleDirection = Direction::DOWN;
	peoplePosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
}

SpecialEvent03::~SpecialEvent03()
{

}

void SpecialEvent03::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		vector<string> messages;
		messages.push_back("おお、よくぞ参られた！");
		messages.push_back("話はカピス村の村長から聞いていると思うが、今朝モナジ洞窟で魔王が復活したみたいでの。");
		messages.push_back("魔王討伐のためにお主らを呼び出したわけじゃ。");
		messages.push_back("突然のことで困惑しているじゃろうが、わしもまさかの事態に混乱しておる。");
		messages.push_back("お主らの力を見込んでさっそく魔王討伐に向かってほしいところなのじゃが、今朝の地震のせいでモナジ洞窟へと続く橋が壊れてしまっての。");
		messages.push_back("どうにかしてその橋の修復をしなければならんのじゃが、この村には橋を修復できるほどの技術を持った者がおらんのじゃよ。");
		messages.push_back("そこでじゃ、お主らにはこの村から東に進んだところにあるロハス村に向かってほしいのじゃ。");
		messages.push_back("ロハス村には腕の立つ職人がいると聞いておる。");
		messages.push_back("まずは、ロハス村に行って橋の修復ができないかその者と相談してほしいのじゃよ。");
		messages.push_back("ロハス村までの距離はかなりあるでの、気を付けて行ってくるのじゃ。");
		windowList.push_back(make_shared<MessageWindow>("村長", messages));
	}
	if (140 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 240)
	{
		endFlag = true;
	}
}

void SpecialEvent03::Draw()
{
	Vector2<int> offset = Vector2<int>(37, 31);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[95].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[95].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapBackChip[MapInfoList::GetMapInfoList()[100].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[95].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[95].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[100].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[95].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[95].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[100].mapObject[1][pos.y][pos.x]], TRUE);
		}
	}

	DrawRotaGraph(playerPosition.x, playerPosition.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + 1], TRUE);
	DrawRotaGraph(peoplePosition.x, peoplePosition.y, 1.0, 0.0, peopleGraph[14][(int)peopleDirection * 3 + 1], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}