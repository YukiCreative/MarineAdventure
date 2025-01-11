#include "SceneTitle.h"
#include <DxLib.h>
#include "SceneController.h"
#include <cassert>
#include "game.h"
#include <memory>
#include "BackGround.h"
#include "Camera.h"
#include "ScreenFade.h"
#include "TestScene.h"
#include "ButtonSystem.h"
#include "ButtonGameStart.h"
#include "Music.h"

namespace
{
	const Vector2 kScreenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	constexpr int kButtonYOffset = 80;
	const Vector2 kInitButtonPos(Game::kScreenHalfWidth, Game::kScreenHeight - kButtonYOffset);
	const std::string kBGPath   = "Marine.jpg";
	const std::string kLogoPath = "Logo.png";
}

SceneTitle::SceneTitle()
{
	m_camera       = std::make_shared<Camera>      ();
	m_buttonSystem = std::make_shared<ButtonSystem>();
	m_backGround   = std::make_shared<ImageObject> (*m_camera, Vector2::Zero(), kBGPath);
	m_titleLogo    = std::make_shared<ImageObject> (*m_camera, Vector2::Zero(), kLogoPath);

	std::shared_ptr<ButtonGameStart> buttonGameStart = std::make_shared<ButtonGameStart>(kInitButtonPos, *this);
	m_buttonSystem->AddButton(buttonGameStart);
	m_buttonSystem->SetButtonFocus(buttonGameStart);
}

void SceneTitle::Entry()
{
	Music::GetInstance().Play("Data/Music/’‹‰º‚ª‚è‹C•ª.mp3");
	m_fade.Fade(60, 0);
}

void SceneTitle::NormalUpdate()
{
	m_camera->Update();
	m_buttonSystem->Update();
	m_fade.Update();
}

void SceneTitle::Draw() const
{
	m_backGround->Draw();
	m_titleLogo->Draw();
	m_buttonSystem->Draw();
	m_fade.Draw();
}

void SceneTitle::GameStart()
{
	SceneChangeWithFadeOut("Game");
}