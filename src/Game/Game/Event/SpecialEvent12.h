#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent12 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	int playerMoveTime;
	Direction peopleDirection;
	Vector2<int> peoplePosition;
	int peopleMoveTime;
	int darkAlpha;
private:
	void UpdateEvent()override;
public:
	SpecialEvent12();
	~SpecialEvent12();
	void Draw()override;
};