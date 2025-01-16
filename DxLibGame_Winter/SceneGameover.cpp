#include "SceneGameover.h"
#include <DxLib.h>
#include <memory>
#include "Input.h"
#include "SceneController.h"
#include "game.h"
#include "BackGround.h"
#include "Camera.h"
#include "ScreenFade.h"
#include "Music.h"
#include "ButtonSystem.h"

namespace
{
	const Vector2 kScreenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	const std::string kGameOverImagePath = "GAMEOVER_Test.jpg";
}

SceneGameover::SceneGameover()
{
	m_backGround = std::make_shared<ImageObject>(*m_camera, kScreenMiddlePoint, kGameOverImagePath);
	m_backGround->ExpandGtaph(3.0f);

	m_buttonController = std::make_shared<ButtonSystem>();
}

void SceneGameover::Entry()
{
	Music::GetInstance().Play("Data/Music/降りしきる、白.mp3");
	m_fade.Fade(60, 0);
}

void SceneGameover::NormalUpdate()
{
	m_backGround->Update();
	m_fade.Update();

	if (Input::GetInstance().IsTrigger("ChangeScene_Debug"))
	{
		// シーンが次のシーンをインクルードするのはどうかと思ってる
		// 別に今何かをしようってわけではない
		SceneChangeWithFadeOut("Title");
		return;
	}
}

void SceneGameover::Draw() const
{
	m_backGround->Draw();
	m_fade.Draw();
}

void SceneGameover::ReturnToTitle()
{
	SceneChangeWithFadeOut("Title");
}
