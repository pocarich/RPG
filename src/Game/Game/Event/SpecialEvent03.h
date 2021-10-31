#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent03 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	Direction peopleDirection;
	Vector2<int> peoplePosition;
	int darkAlpha;
private:
	void UpdateEvent()override;
public:
	SpecialEvent03();
	~SpecialEvent03();
	void Draw()override;
};