#include "Time.h"
#include <DxLib.h>

// static�����o�ϐ��̓����o�֐��݂����ɒ�`���Ȃ��Ƃ����Ȃ����ۂ�
float Time::s_fps = 0;
float Time::s_deltaTime = 0;
int   Time::s_frameCount = 0;

Time& Time::GetInstance()
{
	static Time instance;
	return instance;
}

void Time::Update()
{
	++s_frameCount;
	s_fps = GetFPS();
	s_deltaTime = 1 / s_fps;
}

float Time::FPS()
{
	return s_fps;
}

float Time::DeltaTime()
{
	return s_deltaTime;
}

int Time::FrameCount()
{
	return s_frameCount;
}
