#include "TestScene.h"
#include <DxLib.h>
#include "Player.h"
#include "Time.h"

TestScene::TestScene() :
	m_frameCount(0)
{
	m_player = std::make_shared<Player>();
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	++m_frameCount;
	m_player->Update();
}

void TestScene::Draw()
{
	m_player->Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "TestScene Œ»İ%dƒtƒŒ[ƒ€Œo‰ß’†", m_frameCount);
	DrawFormatString(0, 60, 0xffffff, "%fFPS", Time::FPS());
	DrawFormatString(0, 75, 0xffffff, "deltaTime:%f", Time::DeltaTime());
#endif
}
