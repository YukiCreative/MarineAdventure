#include "ButtonGameStart.h"
#include "ButtonQuitGame.h"
#include "ButtonSystem.h"
#include "Camera.h"
#include "game.h"
#include "ImageObject.h"
#include "Music.h"
#include "SceneController.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "ScreenFade.h"
#include <cassert>
#include <DxLib.h>
#include <memory>

namespace
{
	constexpr int kStartButtonInitPosY = Game::kScreenHalfHeight + 200;
	constexpr int kButtonYOffset = 100;
	const Vector2 kInitTitleLogoPos(0, -50);
	// íÜêSÇ©ÇÁÇæÇÒÇæÇÒâ∫Ç…Ç∏ÇÍÇƒÇ¢Ç≠
	const Vector2 kInitStartButtonPos(Game::kScreenHalfWidth, kStartButtonInitPosY);
	const Vector2 kInitQuitButtonPos(kInitStartButtonPos.x, kInitStartButtonPos.y + kButtonYOffset);
	const std::string kBGPath   = "Marine.jpg";
	const std::string kLogoPath = "Logo.png";
}

void SceneTitle::ButtonInit()
{
	m_buttonSystem = std::make_shared<ButtonSystem>();

	std::shared_ptr<ButtonGameStart> buttonGameStart = std::make_shared<ButtonGameStart>(kInitStartButtonPos, *this);
	std::shared_ptr<ButtonQuitGame>  buttonQuitGame  = std::make_shared<ButtonQuitGame> (kInitQuitButtonPos);

	buttonGameStart->SetUpButton  (buttonQuitGame);
	buttonGameStart->SetDownButton(buttonQuitGame);
	buttonQuitGame ->SetUpButton  (buttonGameStart);
	buttonQuitGame ->SetDownButton(buttonGameStart);

	m_buttonSystem->AddButton(buttonGameStart);
	m_buttonSystem->AddButton(buttonQuitGame);

	m_buttonSystem->SetButtonFocus(buttonGameStart);
}

void SceneTitle::Init()
{
	m_backGround = std::make_shared<ImageObject>(*m_camera, Vector2::Zero(), kBGPath);
	m_titleLogo = std::make_shared<ImageObject>(*m_camera, kInitTitleLogoPos, kLogoPath);

	ButtonInit();
}

void SceneTitle::Entry()
{
	Music::GetInstance().Play("Data/Music/íãâ∫Ç™ÇËãCï™.mp3");
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