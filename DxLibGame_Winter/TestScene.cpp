#include "TestScene.h"
#include <DxLib.h>
#include "Player.h"
#include "Time.h"
#include "MapSystem.h"

TestScene::TestScene() :
	m_frameCount(0)
{
	m_map = std::make_shared<MapSystem>();
	m_player = std::make_shared<Player>();
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	++m_frameCount;
	// プレイヤーの更新処理で入手した移動量の情報を
	// マップにぶち込む
	// 方法だとマップの端に来た時にプレイヤーが代わりに動く処理を実装しづらい
	m_player->Update(m_map);
	m_map->Update(m_player);
}

void TestScene::Draw()
{
	m_map->Draw();
	m_player->Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "TestScene 現在%dフレーム経過中", m_frameCount);
	DrawFormatString(0, 60, 0xffffff, "%fFPS", Time::FPS());
	DrawFormatString(0, 75, 0xffffff, "deltaTime:%f", Time::DeltaTime());
#endif
}
