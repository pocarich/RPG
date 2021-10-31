#pragma once

#include"TextUI.h"

class DamageTextPlayer :public TextUI
{
private:
	const double gravity = 0.8;
private:
	int value;
	double defaultY;
	Vector2<double> velocity;
public:
	DamageTextPlayer(Vector2<double>& camera, Vector2<double> position, int value);
	void Update()override;
	void Draw()override;
};