#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent00 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	int darkAlpha;
private:
	void UpdateEvent()override;
public:
	SpecialEvent00();
	~SpecialEvent00();
	void Draw()override;
};