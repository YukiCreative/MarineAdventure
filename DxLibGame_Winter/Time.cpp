#include "Time.h"
#include <DxLib.h>

// staticƒƒ“ƒo•Ï”‚Íƒƒ“ƒoŠÖ”‚İ‚½‚¢‚É’è‹`‚µ‚È‚¢‚Æ‚¢‚¯‚È‚¢‚Á‚Û‚¢
float Time::fps = 0;
float Time::deltaTime = 0;

Time& Time::GetInstance()
{
	static Time instance;
	return instance;
}

void Time::Update()
{
	fps = GetFPS();
	deltaTime = 1 / fps;
}

float Time::FPS()
{
	return fps;
}

float Time::DeltaTime()
{
	return deltaTime;
}
