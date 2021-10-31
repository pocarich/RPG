#include"../header/SpecialEvent02.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent02::SpecialEvent02()
{
	playerDirection = Direction::RIGHT;
	playerPosition = Vector2<int>(32 * 15 + Define::MASU_SIZE / 2, 32 * 7 + Define::MASU_SIZE / 2);
	motherDirection = Direction::UP;
	motherPosition = Vector2<int>(32 * 16 + Define::MASU_SIZE / 2, 32 * 7 + Define::MASU_SIZE / 2);
	ariaDirection = Direction::UP;
	ariaPosition= Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 14 + Define::MASU_SIZE / 2);
	ariaMoveTimer = 0;
	headmanDirection = Direction::UP;
	headmanPosition= Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 14 + Define::MASU_SIZE / 2);
	headmanMoveTimer = 0;
	darkAlpha = 255;
}

SpecialEvent02::~SpecialEvent02()
{

}

void SpecialEvent02::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		motherDirection = Direction::LEFT;
	}
	if (eventTimer == 130)
	{
		vector<string> messages;
		messages.push_back("����A�̂��Ă��Ă��ꂽ�̂ˁB");
		messages.push_back("���肪�Ƃ��A�N���X�B");
		messages.push_back("���ꂶ�Ⴀ���ꂩ��V�`���[����邩�炿����Ƒ҂��ĂĂˁB");
		windowList.push_back(make_shared<MessageWindow>("�}�}", messages));
	}
	if (190 <= eventTimer&&eventTimer < 198)
	{
		headmanPosition.y -= 4;
		headmanMoveTimer++;
	}
	if (eventTimer == 198)
	{
		headmanDirection = Direction::RIGHT;
	}
	if (198 <= eventTimer&&eventTimer < 214)
	{
		headmanPosition.x += 4;
		headmanMoveTimer++;
	}
	if (eventTimer == 214)
	{
		headmanDirection = Direction::UP;
		headmanMoveTimer = 0;
	}
	if (198 <= eventTimer&&eventTimer < 206)
	{
		ariaPosition.y -= 4;
		ariaMoveTimer++;
	}
	if (eventTimer == 206)
	{
		ariaDirection = Direction::RIGHT;
	}
	if (206 <= eventTimer&&eventTimer < 214)
	{
		ariaPosition.x += 4;
		ariaMoveTimer++;
	}
	if (eventTimer == 214)
	{
		ariaDirection = Direction::UP;
		ariaMoveTimer = 0;
	}
	if (eventTimer == 220)
	{
		windowList.push_back(make_shared<MessageWindow>("����", "��ς���I"));
	}
	if (eventTimer == 230)
	{
		playerDirection = Direction::DOWN;
		motherDirection = Direction::DOWN;
	}
	if (eventTimer == 240)
	{
		windowList.push_back(make_shared<MessageWindow>("�}�}", "����A��������B����ȂɍQ�ĂĂǂ����܂����́H"));
	}
	if (eventTimer == 241)
	{
		vector<string> messages;
		messages.push_back("�J���G�b�g������ǂ��Ȃ��m�点�������ẮB");
		messages.push_back("�J���G�b�g���̖k�ɂ��郂�i�W���A�ɖ��������ꂽ�炵���̂���B");
		windowList.push_back(make_shared<MessageWindow>("����", messages));
	}
	if (eventTimer == 242)
	{
		vector<string> messages;
		messages.push_back("���������ꂽ�ł����āH");
		messages.push_back("�����͑�̂ɕ��󂳂ꂽ�͂����Ⴀ�E�E�E�B");
		windowList.push_back(make_shared<MessageWindow>("�}�}", messages));
	}
	if (eventTimer == 243)
	{
		vector<string> messages;
		messages.push_back("�킵���ڂ������Ƃ͂킩��ʂ��A�����炭���󂪉�����Ă��܂����̂���낤�B");
		messages.push_back("����ł���B");
		messages.push_back("�N���X�ƃA���A�̂Q�l�ɖ��������ւƌ������Ăق����̂���B");
		messages.push_back("���̂�����ŗ͂̂���l�ނƂ������炨��炵�������̂���B");
		messages.push_back("�ǂ����A���܂�Ă͂���ʂ��B");
		windowList.push_back(make_shared<MessageWindow>("����", messages));
	}
	if (eventTimer == 300)
	{
		vector<string> messages;
		messages.push_back("�悭�킩��Ȃ�����ǁA���̊�@�Ƃ��Ȃ�Ζق��Ă͂����Ȃ���ˁB");
		messages.push_back("�������N���X��������ˁH");
		windowList.push_back(make_shared<MessageWindow>("�A���A", messages));
	}
	if (eventTimer == 360)
	{
		vector<string> messages;
		messages.push_back("�������A�Q�l�Ƃ��s���Ă���邩�B");
		messages.push_back("���ꂶ�Ⴀ�܂��̓J���G�b�g���֌������̂���B");
		messages.push_back("�����ɂ͂������񖂕����������Ă���B��������Ə����𐮂��Ă���䂭�̂��Ⴜ�B");
		windowList.push_back(make_shared<MessageWindow>("����", messages));
	}
	if (400 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 500)
	{
		endFlag = true;
	}
}

void SpecialEvent02::Draw()
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

	DrawRotaGraph(playerPosition.x, playerPosition.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + 1], TRUE);
	DrawRotaGraph(motherPosition.x, motherPosition.y, 1.0, 0.0, peopleGraph[10][(int)motherDirection * 3 + 1], TRUE);

	if (190 <= eventTimer)
	{
		int animationFrame;
		if (headmanMoveTimer != 0)
		{
			animationFrame = ((headmanMoveTimer + 8) / 4) % 3;
		}
		else
		{
			animationFrame = 1;
		}

		DrawRotaGraph(headmanPosition.x, headmanPosition.y, 1.0, 0.0, peopleGraph[12][(int)headmanDirection * 3 + 1], TRUE);
	}
	if (198 <= eventTimer)
	{
		int animationFrame;
		if (ariaMoveTimer != 0)
		{
			animationFrame = ((ariaMoveTimer + 8) / 4) % 3;
		}
		else
		{
			animationFrame = 1;
		}

		DrawRotaGraph(ariaPosition.x, ariaPosition.y, 1.0, 0.0, playerGraph[1][(int)headmanDirection * 3 + 1], TRUE);
	}

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}