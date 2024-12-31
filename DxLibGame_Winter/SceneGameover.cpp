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
	const Vector2 kScreenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
}

SceneGameover::SceneGameover()
{
	m_camera = std::make_shared<Camera>();
	m_backGround = std::make_shared<BackGround>(*m_camera, kScreenMiddlePoint, "Data/Image/GAMEOVER_Test.jpg");
	m_backGround->ExpandGtaph(3.0f);
}

void SceneGameover::Entry()
{

}

void SceneGameover::NormalUpdate()
{
	m_backGround->Update();

	if (Input::GetInstance().IsTrigger("ChangeScene_Debug"))
	{
		// シーンが次のシーンをインクルードするのはどうかと思ってる
		// 別に今何かをしようってわけではない
		SceneController::GetInstance().ChangeScene("Title");
		return;
	}
}

void SceneGameover::Draw() const
{
	m_backGround->Draw();

	DrawString(static_cast<int>(Game::kScreenWidth * 0.5f), static_cast<int>(Game::kScreenHeight * 0.5f), "GameoverScene", 0xffffff);
}
