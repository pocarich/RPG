#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent21 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	int playerMoveTime;
	Direction peopleDirection;
	Vector2<int> peoplePosition;
	int peopleMoveTime;
	Vector2<int> bossPosition1;
	Vector2<int> bossPosition2;
	int darkAlpha;
	Vector2<int> shake;
	Vector2<int> camera;
private:
	void UpdateEvent()override;
public:
	SpecialEvent21();
	~SpecialEvent21();
	void Draw()override;
};