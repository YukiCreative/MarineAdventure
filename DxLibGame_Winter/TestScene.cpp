#include "BackGround.h"
#include "Camera.h"
#include "ColliderTestScene.h"
#include "game.h"
#include "Input.h"
#include "MapSystem.h"
#include "ObjectKind.h"
#include "ObjectsController.h"
#include "ScenePause.h"
#include "Player.h"
#include "SceneController.h"
#include "SceneGameover.h"
#include "ScreenFade.h"
#include "TestScene.h"
#include "Time.h"
#include <DxLib.h>
#include "Music.h"

namespace
{
	const Vector2 kScreenMiddlePos(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	const Vector2 initPlayerPos(0, 800);
	const std::string kMapDataPass = "Data/MapData/TestMapGroundStage.fmf";
	const std::string kBackGroundPass = "Marine.jpg";
}

TestScene::TestScene() :
	m_frameCount(0)
{
	m_player     = std::make_shared<Player>           (*m_camera, initPlayerPos);
	m_objectCont = std::make_shared<ObjectsController>(*m_camera, *m_player);
	m_map        = std::make_shared<MapSystem>        (*m_camera, *m_objectCont, kMapDataPass);
	m_backGround = std::make_shared<ImageObject>      (*m_camera, (m_map->GetMapSize() * 16), kBackGroundPass);

	m_player->Init(m_map);

	m_camera->SetFollowObject(m_player);
	m_camera->SetMapSize(m_map->GetMapSize());
	m_backGround->ExpandGtaph(2.0f);
}

TestScene::~TestScene()
{
}

void TestScene::GameClear()
{
	SceneChangeWithFadeOut("Clear");
}

void TestScene::GameOver()
{
	SceneChangeWithFadeOut("Gameover", 120);
}

void TestScene::ChangeMapWithFadeOut(const std::string& path, const Vector2& playerTransferPos)
{

}

void TestScene::ChangeMap(const std::string& path)
{
	m_map->ChangeMapData(path);
	m_camera->SetMapSize(m_map->GetMapSize());
}

void TestScene::ChangeMap(const std::string& path, const Vector2& playerTransferPos)
{
	// 別のfmfファイルを読み込めばいいんやな
	m_map->ChangeMapData(path);
	// 新しいマップのカメラの制限を把握
	m_camera->SetMapSize(m_map->GetMapSize());
	m_player->Teleportation(playerTransferPos);
}

void TestScene::Entry()
{
	// 主にフェード
	m_fade.Fade(60, 0);

	Music::GetInstance().Play("Data/Music/たぬきちの冒険.mp3");
	Music::GetInstance().SetVolume(255);
}

void TestScene::NormalUpdate()
{
	Input& input = Input::GetInstance();

	++m_frameCount;
	m_camera->Update();
	m_fade.Update();

	m_map->Update();
	m_player->Update();
	m_objectCont->Update();

	// カメラの移動量を取得したい
	//m_backGround->Move(m_camera->GetVel() * 0.5f);
	m_backGround->Update();


	if (input.IsTrigger("Pause"))
	{
		// ここでフェードパネルの色変えたらいいんじゃね
		m_fade.SetColor(0xffffff);
		SceneStackWithFadeOut("Pause", 30);
		return;
	}
	if (input.IsTrigger("ChangeScene_Debug"))
	{
		//SceneChangeWithFadeOut("Clear");
		ChangeMap("Data/MapData/TestMapData32x16.fmf");
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
