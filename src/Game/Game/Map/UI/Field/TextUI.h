#pragma once

#include"Define.h"
#include"Class.h"

class TextUI
{
protected:
	Vector2<double>& camera;
	Vector2<double> position;
	bool deleteFlag;
	int timer;
public:
	TextUI(Vector2<double>& camera, Vector2<double> position);
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool GetDeleteFlag()const { return deleteFlag; }
};