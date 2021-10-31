#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent18 :public SpecialEvent
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
	Vector2<int> camera;
private:
	void UpdateEvent()override;
public:
	SpecialEvent18();
	~SpecialEvent18();
	void Draw()override;
};