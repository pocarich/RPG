#include"../header/SpecialEvent15.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent15::SpecialEvent15()
{
	state = 0;
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 13 + Define::MASU_SIZE / 2);
	playerMoveTime = 0;
	player2Direction = Direction::UP;
	player2Position = Vector2<int>(32 * 13 + Define::MASU_SIZE / 2, 32 * 13 + Define::MASU_SIZE / 2);
	player2MoveTime = 0;
	bossPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 5 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
	whiteAlpha = 255;
	circleScale = 0.0;
	shake = Vector2<int>(0, 0);
	mayorPosition= Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 10 + Define::MASU_SIZE / 2);
	mayorMoveTime = 0;

	peoplePositionList.push_back(Vector2<int>(32 * 11 + Define::MASU_SIZE / 2, 32 * 11 + Define::MASU_SIZE / 2));
	peoplePositionList.push_back(Vector2<int>(32 * 10 + Define::MASU_SIZE / 2, 32 * 11 + Define::MASU_SIZE / 2));
	peoplePositionList.push_back(Vector2<int>(32 * 9 + Define::MASU_SIZE / 2, 32 * 12 + Define::MASU_SIZE / 2));
	peoplePositionList.push_back(Vector2<int>(32 * 13 + Define::MASU_SIZE / 2, 32 * 11 + Define::MASU_SIZE / 2));
	peoplePositionList.push_back(Vector2<int>(32 * 14 + Define::MASU_SIZE / 2, 32 * 12 + Define::MASU_SIZE / 2));
	peoplePositionList.push_back(Vector2<int>(32 * 15 + Define::MASU_SIZE / 2, 32 * 11 + Define::MASU_SIZE / 2));
	peoplePositionList.push_back(Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 12 + Define::MASU_SIZE / 2));
	peoplePositionList.push_back(Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 13 + Define::MASU_SIZE / 2));
	peoplePositionList.push_back(Vector2<int>(32 * 11 + Define::MASU_SIZE / 2, 32 * 13 + Define::MASU_SIZE / 2));
	peoplePositionList.push_back(Vector2<int>(32 * 13 + Define::MASU_SIZE / 2, 32 * 13 + Define::MASU_SIZE / 2));

	peopleKindList.push_back(16);
	peopleKindList.push_back(18);
	peopleKindList.push_back(7);
	peopleKindList.push_back(5);
	peopleKindList.push_back(13);
	peopleKindList.push_back(10);
	peopleKindList.push_back(15);
	peopleKindList.push_back(8);
	peopleKindList.push_back(6);
	peopleKindList.push_back(0);
}

SpecialEvent15::~SpecialEvent15()
{

}

void SpecialEvent15::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		vector<string> messages;
		messages.push_back("�n���ȁE�E�E�A�M�l��l�Ԃ̂ǂ��ɂ���ȗ͂��E�E�E�B");
		messages.push_back("�K�A�A�A�A�A�A�A�A�A�A�A�A�A�A�A�A�A�A�A�A�A�I");
		windowList.push_back(make_shared<MessageWindow>("����", messages));
	}
	if (110 <= eventTimer&&eventTimer < 125)
	{
		circleScale += 50;
	}
	if (230 <= eventTimer&&eventTimer < 330)
	{
		whiteAlpha -= 3;
		whiteAlpha = max(whiteAlpha, 0);
	}
	if (110 <= eventTimer&&eventTimer < 380)
	{
		if (2 <= (eventTimer - 110) % 8 && (eventTimer - 110) % 8 < 6)
		{
			shake.x++;
		}
		else
		{
			shake.x--;
		}
	}
	if (eventTimer == 380)
	{
		shake = Vector2<int>(0, 0);
	}
	if (380 < eventTimer&&eventTimer<480)
	{
		darkAlpha += 5;
		darkAlpha = min(darkAlpha, 255);
	}
	if (eventTimer == 480)
	{
		state++;
		playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * (-1) + Define::MASU_SIZE / 2);
		player2Position = Vector2<int>(32 * 13 + Define::MASU_SIZE / 2, 32 * (-1) + Define::MASU_SIZE / 2);
		playerDirection = Direction::DOWN;
		player2Direction = Direction::DOWN;
	}
	if (600 <= eventTimer&&eventTimer < 700)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (600 <= eventTimer&&eventTimer < 856)
	{
		playerPosition.y++;
		player2Position.y++;
		playerMoveTime++;
		player2MoveTime++;
	}
	if (eventTimer == 856)
	{
		playerMoveTime = 0;
		player2MoveTime = 0;
	}
	if (880 <= eventTimer&&eventTimer < 912)
	{
		mayorPosition.y--;
		mayorMoveTime++;
	}
	if (eventTimer == 912)
	{
		mayorMoveTime = 0;
	}
	if (eventTimer == 930)
	{
		vector<string> messages;
		messages.push_back("�N���X�a�A�A���A�a�A�����ɖ�����|���ċA���Ă���ꂽ�悤�ł��ȁE�E�E�B");
		messages.push_back("������ᏋC����������Ə����ĂȂ��Ȃ����݂����ŁA�������܂ŋ����Ă������l�������݂�Ȃ������茳�C�����߂����݂�������B");
		messages.push_back("�����ɂ͂Ȃ�Ƃ����\���グ����悢���E�E�E�B���ӂ��悤�ɂ����ӂ�����ʎv������B");
		messages.push_back("���̑��A���₱�̑嗤���\���Ă����\���グ�܂����A�{���ɂ��肪�Ƃ��B");
		messages.push_back("��������A�߁X���̑��ōՂ���Â����ƌv��𗧂ĂĂ��ẮA����ƌ����Ă͂Ȃ񂶂Ⴊ�����ɂ͂��Ђ��̍Ղ�ɎQ�����Ăق����̂���B");
		messages.push_back("���l�ꓯ�A����ɂ��ĂȂ��č����グ�܂����I");
		windowList.push_back(make_shared<MessageWindow>("����", messages));
	}
	if (960 < eventTimer&&eventTimer<1160)
	{
		darkAlpha += 5;
		darkAlpha = min(darkAlpha, 255);
	}
	if (eventTimer == 1160)
	{
		state++;
		darkAlpha = 0;
		vector<string> messages;
		messages.push_back("�Q�[���N���A���߂łƂ��������܂��I");
		messages.push_back("���̌�̓��X�{�X���j�O�̏󋵂ɖ߂�A�`���𑱍s���邱�Ƃ��ł��܂��B�i���X�{�X���j�̋Ɛт͕ۑ�����܂��B�j");
		messages.push_back("�Ɛт̃R���v���[�g��B���C�x���g���A�N���A��������Ċy����ł���������ƍK���ł��B");
		windowList.push_back(make_shared<MessageWindow>("", messages));
	}
	if (eventTimer == 1280)
	{
		endFlag = true;
	}
}

void SpecialEvent15::Draw()
{
	switch (state)
	{
	case 0:
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
				DrawGraphF((float)Define::MASU_SIZE*j + shake.x, (float)Define::MASU_SIZE*i + shake.y, mapBackChip[MapInfoList::GetMapInfoList()[89].mapChip[pos.y][pos.x]], TRUE);
			}
		}

		for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
		{
			Vector2<int> pos = offset + Vector2<int>(j, i);
			if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[89].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[89].widthNum)
			{
				DrawGraphF((float)Define::MASU_SIZE*j + shake.x, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[89].mapObject[0][pos.y][pos.x]], TRUE);
			}
		}

		for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
		{
			Vector2<int> pos = offset + Vector2<int>(j, i);
			if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[89].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[89].widthNum)
			{
				DrawGraphF((float)Define::MASU_SIZE*j + shake.x, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[89].mapObject[1][pos.y][pos.x]], TRUE);
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
			DrawRotaGraph(playerPosition.x + shake.x, playerPosition.y + shake.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + animationFrame], TRUE);
		}
		{
			int animationFrame;
			if (player2MoveTime != 0)
			{
				animationFrame = ((player2MoveTime + 8) / 4) % 3;
			}
			else
			{
				animationFrame = 1;
			}
			DrawRotaGraph(player2Position.x + shake.x, player2Position.y + shake.y, 1.0, 0.0, peopleGraph[30][(int)player2Direction * 3 + animationFrame], TRUE);
		}

		if (eventTimer < 170)
		{
			DrawRotaGraph(bossPosition.x + shake.x, bossPosition.y + shake.y, 1.0, 0.0, bossGraph[2], TRUE);
		}

		Function::Alpha(whiteAlpha);
		DrawCircle(32 * 12 + Define::MASU_SIZE / 2, 32 * 5 + Define::MASU_SIZE / 2, (int)circleScale, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], TRUE);
		Function::Alpha(255);
	}
		break;
	case 1:
	{
		Vector2<int> offset = Vector2<int>(50, 5);
		int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
		int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
		lengthX += 2;
		lengthY += 2;

		for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
		{
			Vector2<int> pos = offset + Vector2<int>(j, i);
			if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
			{
				DrawGraphF((float)Define::MASU_SIZE*j + shake.x, (float)Define::MASU_SIZE*i + shake.y, mapBackChip[MapInfoList::GetMapInfoList()[15].mapChip[pos.y][pos.x]], TRUE);
			}
		}

		for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
		{
			Vector2<int> pos = offset + Vector2<int>(j, i);
			if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
			{
				DrawGraphF((float)Define::MASU_SIZE*j + shake.x, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[15].mapObject[0][pos.y][pos.x]], TRUE);
			}
		}

		for (int i = 0; i < lengthY + 20; i++)for (int j = 0; j < lengthX; j++)
		{
			Vector2<int> pos = offset + Vector2<int>(j, i);
			if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
			{
				DrawGraphF((float)Define::MASU_SIZE*j + shake.x, (float)Define::MASU_SIZE*i + shake.y, mapObjectChip[MapInfoList::GetMapInfoList()[15].mapObject[1][pos.y][pos.x]], TRUE);
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
			DrawRotaGraph(playerPosition.x + shake.x, playerPosition.y + shake.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + animationFrame], TRUE);
		}
		{
			int animationFrame;
			if (player2MoveTime != 0)
			{
				animationFrame = ((player2MoveTime + 8) / 4) % 3;
			}
			else
			{
				animationFrame = 1;
			}
			DrawRotaGraph(player2Position.x + shake.x, player2Position.y + shake.y, 1.0, 0.0, peopleGraph[30][(int)player2Direction * 3 + animationFrame], TRUE);
		}
		{
			int animationFrame;
			if (mayorMoveTime != 0)
			{
				animationFrame = ((mayorMoveTime + 8) / 4) % 3;
			}
			else
			{
				animationFrame = 1;
			}
			DrawRotaGraph(mayorPosition.x + shake.x, mayorPosition.y + shake.y, 1.0, 0.0, peopleGraph[14][(int)Direction::UP * 3 + animationFrame], TRUE);
		}

		for (int i = 0; i != peoplePositionList.size(); i++)
		{
			DrawRotaGraph(peoplePositionList[i].x + shake.x, peoplePositionList[i].y + shake.y, 1.0, 0.0, peopleGraph[peopleKindList[i]][(int)Direction::UP * 3 + 1], TRUE);
		}
	}
		break;
	case 2:
		break;
	}

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}