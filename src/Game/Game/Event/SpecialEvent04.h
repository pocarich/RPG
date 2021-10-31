#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent04 :public SpecialEvent
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
	SpecialEvent04();
	~SpecialEvent04();
	void Draw()override;
};