#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent16 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	Vector2<int> stonePosition;
	int playerMoveTime;
	int darkAlpha;
	Vector2<int> shake;
private:
	void UpdateEvent()override;
public:
	SpecialEvent16();
	~SpecialEvent16();
	void Draw()override;
};