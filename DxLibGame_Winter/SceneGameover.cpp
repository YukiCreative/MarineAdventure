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
#include "ButtonReturnToTitleFromGameover.h"

namespace
{
	const Vector2 kScreenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	const std::string kGameOverImagePath = "GAMEOVER_Test.jpg";

	constexpr int kReturnButtonPosOffset = 60;
	const Vector2 kReturnButtonInitPos(Game::kScreenHalfWidth, Game::kScreenHalfHeight + kReturnButtonPosOffset);
}

SceneGameover::SceneGameover()
{
	m_backGround = std::make_shared<ImageObject>(*m_camera, kScreenMiddlePoint, kGameOverImagePath);
	m_backGround->ExpandGtaph(3.0f);

	m_buttonController = std::make_shared<ButtonSystem>();
	std::shared_ptr<Button> buttonReturnToGame = std::make_shared<ButtonReturnToTitleFromGameover>(kReturnButtonInitPos);
	m_buttonController->AddButton(buttonReturnToGame);
	m_buttonController->SetButtonFocus(buttonReturnToGame);
}

void SceneGameover::Entry()
{
	Music::GetInstance().Play("Data/Music/降りしきる、白.mp3");
	m_fade.Fade(60, 0);
}

void SceneGameover::NormalUpdate()
{
	m_backGround->Update();
	m_buttonController->Update();
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
	m_buttonController->Draw();
	m_fade.Draw();
}

void SceneGameover::ReturnToTitle()
{
	SceneChangeWithFadeOut("Title");
}
