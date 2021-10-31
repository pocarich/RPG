#include"../header/DropEXPText.h"
#include"../header/ColorMgr.h"
#include"../header/FontMgr.h"
#include"../header/Function.h"

DropEXPText::DropEXPText(Vector2<double>& camera, Vector2<double> position, int value) :TextUI(camera, position), value(value)
{

}

void DropEXPText::Update()
{
	position.y -= up_y;
	if (timer == 60)
	{
		deleteFlag = true;
	}
	timer++;
}

void DropEXPText::Draw()
{
	stringstream ss;
	ss << value;
	DrawFormatStringToHandle(Function::CalcCenterOfString(position.x - Define::MASU_SIZE / 2, position.x + Define::MASU_SIZE / 2, FontMgr::GetFont()[9], ss.str().c_str()) - camera.x, position.y - camera.y, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::LIGHTBLUE], FontMgr::GetFont()[9], "%d", value);
}