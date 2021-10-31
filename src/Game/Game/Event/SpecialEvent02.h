#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent02 :public SpecialEvent
{
	Direction playerDirection;
	Vector2<int> playerPosition;
	Direction motherDirection;
	Vector2<int> motherPosition;
	Direction ariaDirection;
	Vector2<int> ariaPosition;
	int ariaMoveTimer;
	Direction headmanDirection;
	Vector2<int> headmanPosition;
	int headmanMoveTimer;
	int darkAlpha;
private:
	void UpdateEvent()override;
public:
	SpecialEvent02();
	~SpecialEvent02();
	void Draw()override;
};