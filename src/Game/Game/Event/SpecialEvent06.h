#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent06 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	Direction peopleDirection;
	Vector2<int> peoplePosition;
	int darkAlpha;
private:
	void UpdateEvent()override;
public:
	SpecialEvent06();
	~SpecialEvent06();
	void Draw()override;
};