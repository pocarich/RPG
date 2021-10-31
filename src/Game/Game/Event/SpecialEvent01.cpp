#include"../header/SpecialEvent01.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent01::SpecialEvent01()
{
	playerDirection = Direction::DOWN;
	playerPosition = Vector2<int>(32 * 7 + Define::MASU_SIZE / 2, 32 * 5 + Define::MASU_SIZE / 2);
	playerMoveTime = 0;
	motherDirection = Direction::UP;
	motherPosition = Vector2<int>(32 * 16 + Define::MASU_SIZE / 2, 32 * 7 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
}

SpecialEvent01::~SpecialEvent01()
{

}

void SpecialEvent01::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (0 <= eventTimer&&eventTimer <128)
	{
		playerPosition.y ++;
		playerMoveTime++;
	}
	if (eventTimer == 128)
	{
		playerDirection = Direction::RIGHT;
	}
	if (128 <= eventTimer&&eventTimer < 160)
	{
		playerPosition.x ++;
		playerMoveTime++;
	}
	if (eventTimer == 160)
	{
		playerMoveTime = 0;
	}
	if (eventTimer == 180)
	{
		motherDirection = Direction::LEFT;
	}
	if (eventTimer == 200)
	{
		vector<string> messages;
		messages.push_back("おはよう、クリス。");
		messages.push_back("寝起きで悪いんだけれど少しおつかいを頼まれてくれないかしら。");
		messages.push_back("今朝きのこのシチューを作ろうと思っていたんだけれど、ちょうどきのこを切らしててね。");
		messages.push_back("森に行ってきのこを３つ採ってきて欲しいのよ。");
		messages.push_back("わかっていると思うけれど、森には魔物がうろついているから注意するのよ。");
		messages.push_back("それじゃあお願いね。");
		windowList.push_back(make_shared<MessageWindow>("ママ", messages));
	}
	if (230 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 330)
	{
		endFlag = true;
	}
}

void SpecialEvent01::Draw()
{
	Vector2<int> offset = Vector2<int>(16, 19);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[95].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[95].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapBackChip[MapInfoList::GetMapInfoList()[94].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[95].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[95].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[94].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[95].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[95].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[94].mapObject[1][pos.y][pos.x]], TRUE);
		}
	}

	int animationFrame;
	if (playerMoveTime != 0)
	{
		animationFrame = ((playerMoveTime + 8) / 4) % 3;
	}
	else
	{
		animationFrame = 1;
	}

	DrawRotaGraph(playerPosition.x, playerPosition.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + animationFrame], TRUE);
	DrawRotaGraph(motherPosition.x, motherPosition.y, 1.0, 0.0, peopleGraph[10][(int)motherDirection * 3 + 1], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}