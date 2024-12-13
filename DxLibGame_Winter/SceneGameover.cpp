#include "SceneGameover.h"
#include <DxLib.h>
#include <memory>
#include "Input.h"
#include "SceneController.h"
#include "SceneTitle.h"
#include "game.h"
#include "BackGround.h"
#include "Camera.h"

namespace
{
	constexpr int kScreenHalfWidth = Game::kScreenWidth >> 1;
	constexpr int kScreenHalfHeight = Game::kScreenHeight >> 1;
	const Vector2 kScreenMiddlePoint(kScreenHalfWidth, kScreenHalfHeight);
}

SceneGameover::SceneGameover()
{
	m_camera = std::make_shared<Camera>();
	m_backGround = std::make_shared<BackGround>(*m_camera, kScreenMiddlePoint, "Data/Image/GAMEOVER_Test.jpg");
}

void SceneGameover::Update()
{
	m_backGround->Update();

	if (Input::GetInstance().IsTrigger("ChangeScene_Debug"))
	{
		// シーンが次のシーンをインクルードするのはどうかと思ってる
		// 別に今何かをしようってわけではない
		SceneController::GetInstance().ChangeScene(std::make_shared<SceneTitle>());
		return;
	}

	UpdateScreenEffect();
}

void SceneGameover::Draw() const
{
	m_backGround->Draw();

	DrawString(static_cast<int>(Game::kScreenWidth * 0.5f), static_cast<int>(Game::kScreenHeight * 0.5f), "GameoverScene", 0xffffff);

	DrawScreenEffect();
}
