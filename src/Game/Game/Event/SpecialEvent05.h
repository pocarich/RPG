#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent05 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	int playerMoveTime;
	Direction peopleDirection;
	Vector2<int> peoplePosition;
	int darkAlpha;
private:
	void UpdateEvent()override;
public:
	SpecialEvent05();
	~SpecialEvent05();
	void Draw()override;
};