#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent01 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	int playerMoveTime;
	Direction motherDirection;
	Vector2<int> motherPosition;
	int darkAlpha;
private:
	void UpdateEvent()override;
public:
	SpecialEvent01();
	~SpecialEvent01();
	void Draw()override;
};