#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent13 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	Direction peopleDirection;
	Vector2<int> peoplePosition;
	int darkAlpha;
private:
	void UpdateEvent()override;
public:
	SpecialEvent13();
	~SpecialEvent13();
	void Draw()override;
};