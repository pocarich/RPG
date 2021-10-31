#include"../header/TextUI.h"

TextUI::TextUI(Vector2<double>& camera, Vector2<double> position) :camera(camera), position(position)
{
	timer = 0;
	deleteFlag = false;
}