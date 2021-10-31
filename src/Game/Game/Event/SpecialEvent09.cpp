#include"../header/SpecialEvent09.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent09::SpecialEvent09()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	peopleDirection = Direction::DOWN;
	peoplePosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 8 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
}

SpecialEvent09::~SpecialEvent09()
{

}

void SpecialEvent09::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		vector<string> messages;
		messages.push_back("���A��������Ⴂ�܂����ˁB");
		messages.push_back("���̌��Ȃ�ł����A���͎v�����ȏ�ɖ����ɂ�閂�͂̐Z�H���[���ŁA���̖؍ނł͂����ɕ��s���Ă��܂��C��������ȏ�ԂȂ̂ł��B");
		messages.push_back("�Z�p�������Ă����̂������Ă͂ǂ����悤������܂���B");
		messages.push_back("�Z�H�ɑς�����؍ނƂ�������^�b�p�[�X�т̉��ɂ��郋�e�B�����ł��傤���B");
		messages.push_back("���̖؂ɂ͐_���ȗ͂�������Ă���ƕ����܂��B�����Ɩ��͂ɂ�镅�s�ɂ��ς����邱�Ƃł��傤�B");
		messages.push_back("�����łł��B���x�������Ă΂���Ő\����Ȃ��̂ł����A�^�b�p�[�X�тɍs���ă��e�B�����̖؍ނ��̂��Ă��Ă������������̂ł��B");
		messages.push_back("�^�b�p�[�X�т͋��J������Ă��΂炭�s�����Ƃ���ɂ���܂��B�ǂ�����낵�����肢���܂��B");
		windowList.push_back(make_shared<MessageWindow>("���l", messages));
	}
	if (eventTimer == 130)
	{
		vector<string> messages;
		messages.push_back("���A�厖�Ȃ��Ƃ������̂�Y��Ă��܂����B");
		messages.push_back("�^�b�p�[�X�т͎����悤�Ȓn�`�������X�ŁA�ꕔ�ł͖����̐X�ȂǂƌĂ΂�Ă��܂��B");
		messages.push_back("�����炭���̏����Ȃ��ɐX�ɓ���͓̂���Ƃ͌����Ȃ��ł��傤�B");
		messages.push_back("�X�ւƌ������O�ɂ�������Ə����W�����邱�Ƃ��������߂��܂��B");
		windowList.push_back(make_shared<MessageWindow>("���l", messages));
	}
	if (160 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 260)
	{
		endFlag = true;
	}
}

void SpecialEvent09::Draw()
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