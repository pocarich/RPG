#include"../header/DropMoneyText.h"
#include"../header/ColorMgr.h"
#include"../header/FontMgr.h"
#include"../header/Function.h"

DropMoneyText::DropMoneyText(Vector2<double>& camera, Vector2<double> position, int value) :TextUI(camera, position), value(value)
{

}

void DropMoneyText::Update()
{
	position.y -= up_y;
	if (timer == 60)
	{
		deleteFlag = true;
	}
	timer++;
}

void DropMoneyText::Draw()
{
	stringstream ss;
	ss << value;
	DrawFormatStringToHandle(Function::CalcCenterOfString(position.x - Define::MASU_SIZE / 2, position.x + Define::MASU_SIZE / 2, FontMgr::GetFont()[9], ss.str().c_str()) - camera.x, position.y - camera.y, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::YELLOW], FontMgr::GetFont()[9], "%d", value);
}