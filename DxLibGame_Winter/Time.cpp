#include "Time.h"
#include <DxLib.h>

// static�����o�ϐ��̓����o�֐��݂����ɒ�`���Ȃ��Ƃ����Ȃ����ۂ�
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
