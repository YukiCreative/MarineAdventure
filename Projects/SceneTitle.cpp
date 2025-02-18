#include "ButtonGameStart.h"
#include "Animation.h"
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
#include "Statistics.h"
#include <cassert>
#include <DxLib.h>
#include <memory>

namespace
{
	constexpr int kStartButtonInitPosY = Game::kScreenHalfHeight + 200;
	constexpr int kButtonYOffset = 100;
	const Vector2 kInitTitleLogoPos(0, -50);
	// 中心からだんだん下にずれていく
	const Vector2 kInitStartButtonPos(Game::kScreenHalfWidth, kStartButtonInitPosY);
	const Vector2 kInitQuitButtonPos(kInitStartButtonPos.x, kInitStartButtonPos.y + kButtonYOffset);
	const std::string kBGPath   = "Marine.jpg";
	const std::string kLogoPath = "Logo.png";
	const std::string kPlayerIdleAnim = "PlayerIdle.png";
	const std::string kPlayerAttackAnim = "PlayerAttack.png";
	const Vector2Int kPlayerSize = { 32, 32 };
	constexpr int kPlaySpeed = 10;
	constexpr int kAttackPlaySpeed = 3;
	const Vector2 kPlayerPos = {200, 600};
	const std::string kMusicFile = "Data/Music/Title.mp3";
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

void SceneTitle::Normal()
{
	m_camera->Update();
	m_buttonSystem->Update();
	m_nowAnim->Update();
	m_fade.Update();
}

void SceneTitle::StartAnim()
{
	m_nowAnim->Update();
	m_fade.Update();

	if (m_fade.IsFading()) return;

	SceneController::GetInstance().ChangeScene("Game");
}

void SceneTitle::Init()
{
	m_state = &SceneTitle::Normal;

	m_backGround = std::make_shared<ImageObject>(*m_camera, Vector2::Zero(), kBGPath);
	m_titleLogo = std::make_shared<ImageObject>(*m_camera, kInitTitleLogoPos, kLogoPath);
	m_playerIdleAnim = std::make_shared<Animation>();
	m_playerAttackAnim = std::make_shared<Animation>();

	m_playerIdleAnim->Init(kPlayerIdleAnim, kPlayerSize, kPlaySpeed);
	m_playerAttackAnim->Init(kPlayerAttackAnim, kPlayerSize, kAttackPlaySpeed);

	m_playerIdleAnim->SetExRate(8);
	m_playerAttackAnim->SetExRate(8);

	m_nowAnim = m_playerIdleAnim;

	ButtonInit();

	// タイトル画面から始めるゲームはステージ1からにする
	SceneGame::ResetStageProgress();
	Statistics::GetInstance().ResetAllScore();
}

void SceneTitle::Entry()
{
	Music::GetInstance().Play(kMusicFile);
	m_fade.Fade(60, 0);
}

void SceneTitle::NormalUpdate()
{
	(this->*m_state)();
}

void SceneTitle::Draw() const
{
	m_backGround->Draw();
	m_titleLogo->Draw();
	m_buttonSystem->Draw();
	m_nowAnim->Draw(kPlayerPos);
	m_fade.Draw();
}

void SceneTitle::GameStart()
{
	m_nowAnim = m_playerAttackAnim;
	m_fade.SetColor(0x000000);
	m_fade.Fade(60, 100);
	m_state = &SceneTitle::StartAnim;
}