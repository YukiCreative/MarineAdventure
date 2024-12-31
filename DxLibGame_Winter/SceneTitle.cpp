#include "SceneTitle.h"
#include <DxLib.h>
#include "Input.h"
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

namespace
{
	const Vector2 kScreenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	constexpr int kButtonYOffset = 80;
	const Vector2 kInitButtonPos(Game::kScreenHalfWidth, Game::kScreenHeight - kButtonYOffset);
}

SceneTitle::SceneTitle()
{
	m_camera = std::make_shared<Camera>();
	m_buttonSystem = std::make_shared<ButtonSystem>(); 
	std::shared_ptr<ButtonGameStart> buttonGameStart = std::make_shared<ButtonGameStart>(kInitButtonPos, *this);
	m_buttonSystem->AddButton(buttonGameStart);
	m_buttonSystem->SetButtonFocus(buttonGameStart);
	// タイトル画像をロード
	m_backGround = std::make_shared<BackGround>(*m_camera, Vector2::Zero(), "Data/Image/Marine.jpg");
}

void SceneTitle::Entry()
{
	m_fade.Fade(60, 0);
}

void SceneTitle::NormalUpdate()
{
	m_camera->Update();
	m_buttonSystem->Update();
	m_fade.Update();
	Input& input = Input::GetInstance();
}

void SceneTitle::Draw() const
{
	m_backGround->Draw();
	m_buttonSystem->Draw();
	m_fade.Draw();
}

void SceneTitle::GameStart()
{
	SceneChangeWithFadeOut("Game");
}