#pragma once

#include"SpecialEvent.h"
#include"Class.h"

class SpecialEvent15 :public SpecialEvent
{
	int state;
	Direction playerDirection;
	Vector2<int> playerPosition;
	int playerMoveTime;
	Direction player2Direction;
	Vector2<int> player2Position;
	int player2MoveTime;
	Vector2<int> bossPosition;
	int darkAlpha;
	int whiteAlpha;
	double circleScale;
	Vector2<int> shake;
	vector<Vector2<int>> peoplePositionList;
	vector<int> peopleKindList;
	Vector2<int> mayorPosition;
	int mayorMoveTime;
private:
	void UpdateEvent()override;
public:
	SpecialEvent15();
	~SpecialEvent15();
	void Draw()override;
};