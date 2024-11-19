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
#include "EnemyController.h"

TestScene::TestScene() :
	m_frameCount(0)
{
	m_camera = std::make_shared<Camera>();
	m_map = std::make_shared<MapSystem>(*m_camera);
	m_player = std::make_shared<Player>(*m_camera);
	m_enemys = std::make_shared<EnemyController>(*m_player, *m_camera);
	m_camera->SetFollowObject(m_player);

	m_enemys->SpawnEnemy(std::make_shared<HarmFish>(*m_camera));
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	Input& input = Input::GetInstance();

	++m_frameCount;
	// プレイヤーの更新処理で入手した移動量の情報を
	// マップにぶち込む
	// 方法だとマップの端に来た時にプレイヤーが代わりに動く処理を実装しづらい
	// ので、シーンに存在するカメラを皆が見て間接的かつ相対的に移動を反映させることにした
	m_camera->Update();
	m_player->Update(*m_map);
	m_map->Update();
	m_enemys->Update();


	if (input.IsTrigger(PAD_INPUT_3))
	{
		SceneController::GetInstance().ChangeScene(std::make_shared<ColliderTestScene>());
		return;
	}
}

void TestScene::Draw()
{
	m_map->Draw();
	m_player->Draw();
	m_enemys->Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0x000000, "TestScene 現在%dフレーム経過中", m_frameCount);
	DrawFormatString(0, 60, 0x000000, "%fFPS", Time::FPS());
	DrawFormatString(0, 75, 0x000000, "deltaTime:%f", Time::DeltaTime());
	DrawFormatString(0, 90, 0x000000, "Cameraのワールド座標:x,%f y,%f", m_camera->GetPos().x, m_camera->GetPos().y);
#endif
}
