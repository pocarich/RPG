#include"../header/SpecialEvent13.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent13::SpecialEvent13()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	peopleDirection = Direction::DOWN;
	peoplePosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 8 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
}

SpecialEvent13::~SpecialEvent13()
{

}

void SpecialEvent13::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		vector<string> messages;
		messages.push_back("おお、無事に採ってこれたみたいですね！");
		messages.push_back("それではさっそく橋の修復に取り掛かります。修復が済むまでしばらく待っていてください。");
		windowList.push_back(make_shared<MessageWindow>("村人", messages));
	}
	if (130 <= eventTimer&&eventTimer < 200)
	{
		darkAlpha += 5;
		darkAlpha = min(darkAlpha, 255);
	}
	if (230 <= eventTimer&&eventTimer < 300)
	{
		darkAlpha -= 5;
		darkAlpha = max(darkAlpha, 0);
	}
	if (eventTimer == 330)
	{
		vector<string> messages;
		messages.push_back("無事修復が完了しました！");
		messages.push_back("これでモナジ洞窟にいけるはずです。");
		messages.push_back("浸食の度合から鑑みるに、魔王の力は計り知れないほど強力です。魔王のもとへ向かう前にしっかりと準備を整えるのがよいでしょう。");
		messages.push_back("それではご武運をお祈りしています。無事に帰ってきてくださいね。");
		windowList.push_back(make_shared<MessageWindow>("村人", messages));
	}
	if (360 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 460)
	{
		endFlag = true;
	}
}

void SpecialEvent13::Draw()
{
	Vector2<int> offset = Vector2<int>(50, 4);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapBackChip[MapInfoList::GetMapInfoList()[15].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[15].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[15].mapObject[1][pos.y][pos.x]], TRUE);
		}
	}

	DrawRotaGraph(playerPosition.x, playerPosition.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + 1], TRUE);
	DrawRotaGraph(peoplePosition.x, peoplePosition.y, 1.0, 0.0, peopleGraph[1][(int)peopleDirection * 3 + 1], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}