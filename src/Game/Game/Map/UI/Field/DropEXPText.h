#pragma once

#include"TextUI.h"

class DropEXPText :public TextUI
{
private:
	const double up_y = 0.3;
private:
	int value;
public:
	DropEXPText(Vector2<double>& camera, Vector2<double> position, int value);
	void Update()override;
	void Draw()override;
};