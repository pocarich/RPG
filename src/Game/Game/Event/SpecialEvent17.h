#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent17 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	int playerMoveTime;
	Direction peopleDirection;
	Vector2<int> peoplePosition;
	int peopleMoveTime;
	Vector2<int> bossPosition;
	int darkAlpha;
	Vector2<int> shake;
private:
	void UpdateEvent()override;
public:
	SpecialEvent17();
	~SpecialEvent17();
	void Draw()override;
};