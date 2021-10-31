#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent22 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	Vector2<int> wallPosition;
	Vector2<int> stonePosition;
	int playerMoveTime;
	int darkAlpha;
	int whiteAlpha;
	Vector2<int> shake;
	Vector2<int> camera;
private:
	void UpdateEvent()override;
public:
	SpecialEvent22();
	~SpecialEvent22();
	void Draw()override;
};