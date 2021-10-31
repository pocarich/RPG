#include"../header/SpecialEvent11.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent11::SpecialEvent11()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	peopleDirection = Direction::UP;
	peoplePosition = Vector2<int>(32 * 11 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
}

SpecialEvent11::~SpecialEvent11()
{

}

void SpecialEvent11::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		vector<string> messages;
		messages.push_back("ふぅ・・・なんとか倒せたみたいね。");
		messages.push_back("気を取り直して奥に進みましょう。");
		windowList.push_back(make_shared<MessageWindow>("アリア", messages));
	}
	if (130 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 230)
	{
		endFlag = true;
	}
}

void SpecialEvent11::Draw()
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
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapBackChip[MapInfoList::GetMapInfoList()[49].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[49].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[49].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[49].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[49].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[49].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[49].mapObject[1][pos.y][pos.x]], TRUE);
		}
	}

	DrawRotaGraph(playerPosition.x, playerPosition.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + 1], TRUE);
	DrawRotaGraph(peoplePosition.x, peoplePosition.y, 1.0, 0.0, peopleGraph[30][(int)peopleDirection * 3 + 1], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}