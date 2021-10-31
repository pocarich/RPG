#pragma once

#include"TextUI.h"

class DropMoneyText :public TextUI
{
private:
	const double up_y = 0.3;
private:
	int value;
public:
	DropMoneyText(Vector2<double>& camera, Vector2<double> position, int value);
	void Update()override;
	void Draw()override;
};