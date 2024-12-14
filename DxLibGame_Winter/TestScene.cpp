#include "TestScene.h"
#include <DxLib.h>
#include "Player.h"
#include "Time.h"
#include "MapSystem.h"
#include "Input.h"
#include "SceneController.h"
#include "ColliderTestScene.h"
#include "Camera.h"
#include "HarmFish.h"
#include "ObjectsController.h"
#include "ObjectKind.h"
#include "SceneGameover.h"
#include "BackGround.h"
#include "game.h"

namespace
{
	const Vector2 kScreenModdlePos(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
}

TestScene::TestScene() :
	m_frameCount(0)
{
	Vector2 initPlayerPos(400, 500);
	m_camera = std::make_shared<Camera>(initPlayerPos);
	m_player = std::make_shared<Player>(*m_camera, initPlayerPos);
	m_objectCont = std::make_shared<ObjectsController>(*m_player, *m_camera);
	m_map = std::make_shared<MapSystem>(*m_camera, *m_objectCont, "Data/MapData/TestMapData32x16.fmf");
	m_backGround = std::make_shared<BackGround>(*m_camera, kScreenModdlePos, "Data/Image/海背景.jpg");

	m_player->Init(m_map);
	m_camera->SetFollowObject(m_player);
	m_camera->SetMapSize(m_map->GetMapSize());
	m_backGround->ExpandGtaph(3.0f);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	Input& input = Input::GetInstance();

	++m_frameCount;
	m_camera->Update();

	m_map->Update();
	m_objectCont->Update();
	m_player->Update();
	// カメラの移動量を取得したい
	m_backGround->Move(m_camera->GetVel() * 0.5f);
	m_backGround->Update();

	if (input.IsTrigger("ChangeScene_Debug"))
	{
		SceneController::GetInstance().ChangeScene(std::make_shared<ColliderTestScene>());
		return;
	}
	if (m_player->IsDeleted())
	{
		// フェードアウトしてシーン遷移
		
		SceneController::GetInstance().ChangeScene(std::make_shared<SceneGameover>());
		return;
	}
}

void TestScene::Draw() const
{
	m_backGround->Draw();
	m_map->Draw();
	m_player->Draw();
	m_objectCont->Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0x999999, "TestScene 現在%dフレーム経過中", m_frameCount);
	DrawFormatString(0, 60, 0x999999, "%fFPS", Time::FPS());
	DrawFormatString(0, 75, 0x999999, "deltaTime:%f", Time::DeltaTime());
	DrawFormatString(0, 90, 0x999999, "Cameraのワールド座標:x,%f y,%f", m_camera->GetPos().x, m_camera->GetPos().y);
#endif
}
