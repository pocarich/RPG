#include"../header/SpecialEvent14.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent14::SpecialEvent14()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 30 + Define::MASU_SIZE / 2, 32 * 19 + Define::MASU_SIZE / 2);
	playerMoveTime = 0;
	peopleDirection = Direction::UP;
	peoplePosition = Vector2<int>(32 * 30 + Define::MASU_SIZE / 2, 32 * 19 + Define::MASU_SIZE / 2);
	peopleMoveTime = 0;
	bossPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 5 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
	shake = Vector2<int>(0, 0);
	camera = Vector2<int>(0, 360);
}

SpecialEvent14::~SpecialEvent14()
{

}

void SpecialEvent14::UpdateEvent()
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
	if (eventTimer == 220)
	{
		vector<string> messages;
		messages.push_back("�N�N�N�E�E�E�i�����肩����������ꂽ���̊J�����A���ɂ������̂��B");
		messages.push_back("���x�����͂��̊��X�������E���ł̕��ɒ��߂Ă���悤�E�E�E�B");
		windowList.push_back(make_shared<MessageWindow>("����", messages));
	}
	if (eventTimer == 220)
	{
		playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 19 + Define::MASU_SIZE / 2);
		peoplePosition = Vector2<int>(32 * 13 + Define::MASU_SIZE / 2, 32 * 19 + Define::MASU_SIZE / 2);
	}
	if (220 <= eventTimer&&eventTimer < 412)
	{
		playerPosition.y--;
		peoplePosition.y--;
		playerMoveTime++;
		peopleMoveTime++;
	}
	if (eventTimer == 412)
	{
		playerMoveTime = 0;
		peopleMoveTime = 0;
	}
	if (eventTimer == 440)
	{
		vector<string> messages;
		messages.push_back("�������ꂽ���E�E�E�����Ȃ�l�ԋ���B");
		messages.push_back("���傤�ǌ����炵�����悤�Ǝv���Ă����Ƃ��낾�B�܂��͋M�l�炩��łɑ��苎���Ă���悤�E�E�E�I");
		windowList.push_back(make_shared<MessageWindow>("����", messages));
	}
	if (470 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 570)
	{
		endFlag = true;
	}
}

void SpecialEvent14::Draw()
{
	Vector2<int> offset = Vector2<int>(26, 14);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[89].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[89].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j-camera.x, (float)Define::MASU_SIZE*i-camera.y + shake.y, mapBackChip[MapInfoList::GetMapInfoList()[89].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[89].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[89].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j-camera.x, (float)Define::MASU_SIZE*i-camera.y + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[89].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[89].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[89].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j-camera.x, (float)Define::MASU_SIZE*i-camera.y + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[89].mapObject[1][pos.y][pos.x]], TRUE);
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
		DrawRotaGraph(playerPosition.x-camera.x, playerPosition.y-camera.y + shake.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + animationFrame], TRUE);
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
		DrawRotaGraph(peoplePosition.x-camera.x, peoplePosition.y-camera.y + shake.y, 1.0, 0.0, peopleGraph[30][(int)peopleDirection * 3 + animationFrame], TRUE);
	}

	DrawRotaGraph(bossPosition.x-camera.x, bossPosition.y-camera.y + shake.y, 1.0, 0.0, bossGraph[2], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}