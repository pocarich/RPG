#include"../header/DamageTextPlayer.h"
#include"../header/ColorMgr.h"
#include"../header/FontMgr.h"

DamageTextPlayer::DamageTextPlayer(Vector2<double>& camera, Vector2<double> position, int value) :TextUI(camera, position), value(value)
{
	velocity = Vector2<double>(0.5, -5.0);
	defaultY = position.y;
}

void DamageTextPlayer::Update()
{
	velocity.y += gravity;
	position += velocity;
	if (position.y >= defaultY)
	{
		velocity.y = -(velocity.y * 1.0);
	}
	if (timer == 40)
	{
		deleteFlag = true;
	}
	timer++;
}

void DamageTextPlayer::Draw()
{
	DrawFormatStringToHandle(position.x - camera.x, position.y - camera.y, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED ], FontMgr::GetFont()[9], "%d", value);
}