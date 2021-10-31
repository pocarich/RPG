#include"../header/SpecialEvent06.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent06::SpecialEvent06()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 10 + Define::MASU_SIZE / 2);
	peopleDirection = Direction::DOWN;
	peoplePosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
}

SpecialEvent06::~SpecialEvent06()
{

}

void SpecialEvent06::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		vector<string> messages;
		messages.push_back("���₨��A������Ȃ��炶��́B����ȂƂ���ɉ��p����H");
		windowList.push_back(make_shared<MessageWindow>("����", messages));
	}
	if (eventTimer == 160)
	{
		vector<string> messages;
		messages.push_back("�Ȃ�ƁA���i�W���A�ł���Ȃ��Ƃ��E�E�E�B");
		messages.push_back("���̏C���Ɋւ��Ă��Ⴊ�A������͍��h�u�����A�ɍz�΍̏W�ɍs���Ă���̂���B");
		messages.push_back("����A���Ă��鎞�Ԃ͂����܂��܂��ł́A�}���̗p�Ȃ̂ł���ΐ��ɐ\����Ȃ��̂��Ⴊ�A�h�u�����A�ɍs���Ă�ɒ��ډ���Ă͂���ʂ��B");
		messages.push_back("�ŋ߃h�u�����A�ɂ͋��͂Ȗ������Z�ݒ����Ă���݂�������B�p�S���Ă䂭�̂��Ⴜ�B");
		windowList.push_back(make_shared<MessageWindow>("����", messages));
	}
	if (200 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 300)
	{
		endFlag = true;
	}
}

void SpecialEvent06::Draw()
{
	Vector2<int> offset = Vector2<int>(32, 27);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[118].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[118].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapBackChip[MapInfoList::GetMapInfoList()[118].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[118].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[118].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[118].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[118].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[118].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[118].mapObject[1][pos.y][pos.x]], TRUE);
		}
	}

	DrawRotaGraph(playerPosition.x, playerPosition.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + 1], TRUE);
	DrawRotaGraph(peoplePosition.x, peoplePosition.y, 1.0, 0.0, peopleGraph[12][(int)peopleDirection * 3 + 1], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}