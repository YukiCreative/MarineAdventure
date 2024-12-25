#include "BackGround.h"
#include "Camera.h"
#include "ColliderTestScene.h"
#include "game.h"
#include "Input.h"
#include "MapSystem.h"
#include "ObjectKind.h"
#include "ObjectsController.h"
#include "PauseScene.h"
#include "Player.h"
#include "SceneController.h"
#include "SceneGameover.h"
#include "ScreenFade.h"
#include "TestScene.h"
#include "Time.h"
#include <DxLib.h>

namespace
{
	const Vector2 kScreenMiddlePos(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	const 	Vector2 initPlayerPos(0, 0);
}

TestScene::TestScene() :
	m_frameCount(0)
{
	m_camera = std::make_shared<Camera>(initPlayerPos);
	m_player = std::make_shared<Player>(*m_camera, initPlayerPos);
	m_objectCont = std::make_shared<ObjectsController>(*m_player, *m_camera);
	m_map = std::make_shared<MapSystem>(*m_camera, *m_objectCont, "Data/MapData/TestMapGroundStage.fmf");
	m_backGround = std::make_shared<BackGround>(*m_camera, (m_map->GetMapSize() * 16), "Data/Image/Marine.jpg");

	m_player->Init(m_map);
	m_camera->SetFollowObject(m_player);
	m_camera->SetMapSize(m_map->GetMapSize());
	m_backGround->ExpandGtaph(2.0f);
	// フェードイン
	m_fade.Fade(60, 0);
}

TestScene::~TestScene()
{
}

void TestScene::NormalUpdate()
{
	Input& input = Input::GetInstance();

	++m_frameCount;
	m_camera->Update();
	m_fade.Update();

	m_map->Update();
	m_objectCont->Update();
	m_player->Update();
	// カメラの移動量を取得したい
	m_backGround->Move(m_camera->GetVel() * 0.5f);
	m_backGround->Update();


	if (input.IsTrigger("Pause"))
	{
		// ここでフェードパネルの色変えたらいいんじゃね
		m_fade.SetColor(0xffffff);
		SceneStackWithFadeOut("Pause", 30);
	}
	if (input.IsTrigger("ChangeScene_Debug"))
	{
		SceneChangeWithFadeOut("ColTest");
		return;
	}
	if (m_player->IsDeleted())
	{
		// フェードアウトしてシーン遷移
		SceneChangeWithFadeOut("Gameover", 120);
		return;
	}
}

void TestScene::Draw() const
{
	m_backGround->Draw();
	m_map->Draw();
	m_player->Draw();
	m_objectCont->Draw();
	m_fade.Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0x999999, "TestScene 現在%dフレーム経過中", m_frameCount);
	DrawFormatString(0, 60, 0x999999, "%fFPS", Time::FPS());
	DrawFormatString(0, 75, 0x999999, "deltaTime:%f", Time::DeltaTime());
	DrawFormatString(0, 90, 0x999999, "Cameraのワールド座標:x,%f y,%f", m_camera->GetPos().x, m_camera->GetPos().y);
#endif
}
