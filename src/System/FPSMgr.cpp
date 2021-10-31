#include"../header/FPSMgr.h"

FPSMgr::FPSMgr()
{
	nowCount = GetNowCount();
	flameCounter = 0;
	takeTimes.fill(0); 

	FPSFont = CreateFontToHandle(NULL, 10, 3, DX_FONTTYPE_EDGE);
	white = GetColor(255, 255, 255);
}

void FPSMgr::Main()
{
	Update();
	DrawFPS();
	Wait();
}

void FPSMgr::Update()
{
	takeTime = GetNowCount() - nowCount;
	nowCount = GetNowCount();
	if (flameCounter == 0)CalcFPS();
	takeTimes[flameCounter] = takeTime;
	flameCounter = (++flameCounter) % Define::FPS;
}

void FPSMgr::CalcFPS()
{
	const double aveSecond = static_cast<double>(accumulate(takeTimes.begin(), takeTimes.end(), 0)) / Define::FPS;
	calcedFPS = 1000.0 / aveSecond;
	if (aveSecond == 0)calcedFPS = 0;
}

void FPSMgr::Wait()
{
	const int waitTime = static_cast<int>(1000.0 / Define::FPS - takeTime);

	if (waitTime > 0)Sleep(waitTime);

	nowCount = GetNowCount();
}

void FPSMgr::DrawFPS()
{
	if (calcedFPS == 0)return;

	DrawFormatStringToHandle(Define::WINDOW_WIDTH - 28, Define::WINDOW_HEIGHT - 12, white, FPSFont, "%.1f", calcedFPS);
}