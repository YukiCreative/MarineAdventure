#include "ButtonContinue.h"
#include "ButtonQuitGameFromGameover.h"
#include "ButtonReturnToTitleFromGameover.h"
#include "ButtonSystem.h"
#include "Camera.h"
#include "game.h"
#include "ImageObject.h"
#include "Input.h"
#include "Music.h"
#include "SceneController.h"
#include "SceneGameover.h"
#include "ScreenFade.h"
#include "SoundManager.h"
#include <DxLib.h>
#include <memory>

namespace
{
	const Vector2 kScreenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	const std::string kBackGroundImageFile = "GAMEOVER_Test.jpg";
	const std::string kPlayerFile = "GameoverPlayer.png";
	const std::string kGameoverTextFile = "GameoverText.png";
	const Vector2 kTextInitPos(Game::kScreenHalfWidth, -100);
	const Vector2 kPlayerInitPos(Game::kScreenHalfWidth, 480);

	const Vector2 kContinueButtonPosOffset(-300, 260);
	constexpr int kButtonShiftOffset       = 300;
	const Vector2 kContinueButtonInitPos   (Game::kScreenHalfWidth + kContinueButtonPosOffset.x, Game::kScreenHalfHeight + kContinueButtonPosOffset.y);
	const Vector2 kReturnTitleButtonInitPos(kContinueButtonInitPos.x + kButtonShiftOffset, kContinueButtonInitPos.y);
	const Vector2 kQuitGameButtonInitPos   (kReturnTitleButtonInitPos.x + kButtonShiftOffset, kReturnTitleButtonInitPos.y);

	// テキストを動かすための値
	constexpr float kTextMoveSpeed = 0.03f;	
	constexpr float kTextMoveRange = 0.4f;

	// 演出用フレーム定数
	// 設定したフレーム数＝演出状態の時間
	constexpr int kPlayerFadeInFrame = 60;
	constexpr int kTextFallFrame = 120;
	constexpr int kButtonAppearFrame = 60;
}

void SceneGameover::ButtonSetting()
{
	m_buttonController = std::make_shared<ButtonSystem>();

	m_buttonContinue = std::make_shared<ButtonContinue>(kContinueButtonInitPos);
	m_buttonReturnToTitle = std::make_shared<ButtonReturnToTitleFromGameover>(kReturnTitleButtonInitPos);
	m_buttonQuitGame      = std::make_shared<ButtonQuitGameFromGameover>(kQuitGameButtonInitPos);

	m_buttonContinue->SetBlendingMode(DX_BLENDMODE_ALPHA, 0);
	m_buttonReturnToTitle->SetBlendingMode(DX_BLENDMODE_ALPHA, 0);
	m_buttonQuitGame->SetBlendingMode(DX_BLENDMODE_ALPHA, 0);

	m_buttonContinue->     SetRightButton(m_buttonReturnToTitle);
	m_buttonContinue->     SetLeftButton (m_buttonQuitGame);
	m_buttonReturnToTitle->SetRightButton(m_buttonQuitGame);
	m_buttonReturnToTitle->SetLeftButton (m_buttonContinue);
	m_buttonQuitGame->     SetRightButton(m_buttonContinue);
	m_buttonQuitGame->     SetLeftButton (m_buttonReturnToTitle);

	m_buttonController->AddButton(m_buttonContinue);
	m_buttonController->AddButton(m_buttonReturnToTitle);
	m_buttonController->AddButton(m_buttonQuitGame);

	m_buttonController->SetButtonFocus(m_buttonContinue);
}

void SceneGameover::PlayerFadeIn()
{
	m_fade.Update();
	// 1秒かけて不透明になる                                    ↓一秒で255になるように設定   ↓状態フレームを秒数に変換
	m_playerDeadSprite->SetImageBlendPal(m_stateFrameCount * (255 / Game::kFrameRate) / (kPlayerFadeInFrame / Game::kFrameRate));

	if (m_stateFrameCount > kPlayerFadeInFrame)
	{
		m_state = &SceneGameover::TextFall;
		m_stateFrameCount = 0;
	}
}

void SceneGameover::TextFall()
{
	m_fade.Update();
	m_gameoverText->Move(Vector2(0, 2));

	if (m_stateFrameCount > kTextFallFrame)
	{
		m_state = &SceneGameover::ButtonAppear;
		m_stateFrameCount = 0;
	}
}

void SceneGameover::ButtonAppear()
{
	m_fade.Update();
	// ボタンの透明度を上げる
	m_buttonContinue->SetBlendingMode(DX_BLENDMODE_ALPHA, m_stateFrameCount * (255 / Game::kFrameRate) / (kButtonAppearFrame / Game::kFrameRate));
	m_buttonReturnToTitle->SetBlendingMode(DX_BLENDMODE_ALPHA, m_stateFrameCount * (255 / Game::kFrameRate) / (kButtonAppearFrame / Game::kFrameRate));
	m_buttonQuitGame->SetBlendingMode(DX_BLENDMODE_ALPHA, m_stateFrameCount * (255 / Game::kFrameRate) / (kButtonAppearFrame / Game::kFrameRate));

	if (m_stateFrameCount > kButtonAppearFrame)
	{
		m_state = &SceneGameover::NormalState;
		m_stateFrameCount = 0;
	}
}

void SceneGameover::NormalState()
{
	m_backGround->Update();
	m_playerDeadSprite->Update();
	m_buttonController->Update();
	// 漂わせたい
	m_gameoverText->Move(Vector2(0.0f, sinf(m_stateFrameCount * kTextMoveSpeed) * kTextMoveRange));
	m_gameoverText->Update();
	m_fade.Update();
}

SceneGameover::SceneGameover() :
	m_stateFrameCount(0),
	m_state(&SceneGameover::PlayerFadeIn)
{
	m_backGround = std::make_shared<ImageObject>(*m_camera, kScreenMiddlePoint, kBackGroundImageFile);
	m_playerDeadSprite = std::make_shared<ImageObject>(*m_camera, kPlayerInitPos, kPlayerFile);
	m_gameoverText = std::make_shared<ImageObject>(*m_camera, kTextInitPos, kGameoverTextFile);

	m_backGround->ExpandGtaph(3.0f);
	m_playerDeadSprite->ExpandGtaph(3.0f);
	m_gameoverText->ExpandGtaph(2.0f);

	ButtonSetting();
}

void SceneGameover::Entry()
{
	Music::GetInstance().Play("Data/Music/降りしきる、白.mp3");
	m_fade.Fade(60, 0);
}

void SceneGameover::NormalUpdate()
{
	++m_stateFrameCount;
	(this->*SceneGameover::m_state)();
}

void SceneGameover::Draw() const
{
	//m_backGround->Draw();
	m_playerDeadSprite->Draw();
	m_buttonController->Draw();
	m_gameoverText->Draw();
	m_fade.Draw();
}

void SceneGameover::ReturnToTitle()
{
	//SoundManager::GetInstance().Play("");
	m_fade.SetColor(0xfffffff);
	SceneChangeWithFadeOut("Title");
}

void SceneGameover::ReturnToGame()
{
	SceneChangeWithFadeOut("Game");
}
