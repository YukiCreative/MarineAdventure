#include "BackGround.h"
#include "ButtonContinue.h"
#include "ButtonQuitGameFromGameover.h"
#include "ButtonReturnToTitleFromGameover.h"
#include "ButtonSystem.h"
#include "Camera.h"
#include "game.h"
#include "Input.h"
#include "Music.h"
#include "SceneController.h"
#include "SceneGameover.h"
#include "ScreenFade.h"
#include <DxLib.h>
#include <memory>

namespace
{
	const Vector2 kScreenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	const std::string kGameOverImagePath = "GAMEOVER_Test.jpg";

	constexpr int kContinueButtonPosOffset = 100;
	constexpr int kButtonShiftOffset       = 100;
	const Vector2 kContinueButtonInitPos   (Game::kScreenHalfWidth, Game::kScreenHalfHeight + kContinueButtonPosOffset);
	const Vector2 kReturnTitleButtonInitPos(kContinueButtonInitPos.x, kContinueButtonInitPos.y + kButtonShiftOffset);
	const Vector2 kQuitGameButtonInitPos   (kReturnTitleButtonInitPos.x, kReturnTitleButtonInitPos.y + kButtonShiftOffset);
}

SceneGameover::SceneGameover()
{
	m_backGround = std::make_shared<ImageObject>(*m_camera, kScreenMiddlePoint, kGameOverImagePath);
	m_backGround->ExpandGtaph(3.0f);

	m_buttonController = std::make_shared<ButtonSystem>();

	std::shared_ptr<Button> buttonReturnToTitle = std::make_shared<ButtonReturnToTitleFromGameover>(kReturnTitleButtonInitPos);
	std::shared_ptr<Button> buttonContinue     = std::make_shared<ButtonContinue>(kContinueButtonInitPos);
	std::shared_ptr<Button> buttonQuitGame     = std::make_shared<ButtonQuitGameFromGameover>(kQuitGameButtonInitPos);

	buttonContinue     ->SetDownButton(buttonReturnToTitle);
	buttonContinue     ->SetUpButton  (buttonQuitGame);
	buttonReturnToTitle->SetDownButton(buttonQuitGame);
	buttonReturnToTitle->SetUpButton  (buttonContinue);
	buttonQuitGame     ->SetDownButton(buttonContinue);
	buttonQuitGame     ->SetUpButton  (buttonReturnToTitle);

	m_buttonController->AddButton(buttonContinue);
	m_buttonController->AddButton(buttonReturnToTitle);
	m_buttonController->AddButton(buttonQuitGame);

	m_buttonController->SetButtonFocus(buttonContinue);
}

void SceneGameover::Entry()
{
	Music::GetInstance().Play("Data/Music/~‚è‚µ‚«‚éA”’.mp3");
	m_fade.Fade(60, 0);
}

void SceneGameover::NormalUpdate()
{
	m_backGround->Update();
	m_buttonController->Update();
	m_fade.Update();
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

void SceneGameover::ReturnToGame()
{
	SceneChangeWithFadeOut("Game");
}
