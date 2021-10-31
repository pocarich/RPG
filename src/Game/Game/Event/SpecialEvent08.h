#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent08 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	Direction peopleDirection;
	Vector2<int> peoplePosition;
	int darkAlpha;
private:
	void UpdateEvent()override;
public:
	SpecialEvent08();
	~SpecialEvent08();
	void Draw()override;
};