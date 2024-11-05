#include "TestScene.h"
#include <DxLib.h>
#include "Player.h"

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
#endif
}
