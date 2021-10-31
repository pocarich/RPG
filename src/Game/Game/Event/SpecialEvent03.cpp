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
		messages.push_back("�����A�悭���Q��ꂽ�I");
		messages.push_back("�b�̓J�s�X���̑������畷���Ă���Ǝv�����A�������i�W���A�Ŗ��������������݂����ł́B");
		messages.push_back("���������̂��߂ɂ������Ăяo�����킯����B");
		messages.push_back("�ˑR�̂��Ƃō��f���Ă��邶��낤���A�킵���܂����̎��Ԃɍ������Ă���B");
		messages.push_back("�����̗͂�������ł����������������Ɍ������Ăق����Ƃ���Ȃ̂��Ⴊ�A�����̒n�k�̂����Ń��i�W���A�ւƑ����������Ă��܂��ẮB");
		messages.push_back("�ǂ��ɂ����Ă��̋��̏C�������Ȃ���΂Ȃ��̂��Ⴊ�A���̑��ɂ͋����C���ł���قǂ̋Z�p���������҂������̂����B");
		messages.push_back("�����ł���A�����ɂ͂��̑����瓌�ɐi�񂾂Ƃ���ɂ��郍�n�X���Ɍ������Ăق����̂���B");
		messages.push_back("���n�X���ɂ͘r�̗��E�l������ƕ����Ă���B");
		messages.push_back("�܂��́A���n�X���ɍs���ċ��̏C�����ł��Ȃ������̎҂Ƒ��k���Ăق����̂����B");
		messages.push_back("���n�X���܂ł̋����͂��Ȃ肠��ł́A�C��t���čs���Ă���̂���B");
		windowList.push_back(make_shared<MessageWindow>("����", messages));
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