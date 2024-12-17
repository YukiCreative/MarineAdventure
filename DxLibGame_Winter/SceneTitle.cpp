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

namespace
{
	const Vector2 kScreenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
}

SceneTitle::SceneTitle() :
	m_fade(ScreenFade::Getinstance())
{
	m_camera = std::make_shared<Camera>();
	// �^�C�g���摜�����[�h
	m_backGround = std::make_shared<BackGround>(*m_camera, kScreenMiddlePoint, "Data/Image/Marine.jpg");
	m_backGround->ExpandGtaph(2.2f);
	m_fade.Fade(60, 0);
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Update()
{
	m_fade.Update();
	Input& input = Input::GetInstance();
	if (input.IsTrigger("ChangeScene_Debug"))
	{
		SceneController::GetInstance().ChangeScene(std::make_shared<TestScene>());
	}
}

void SceneTitle::Draw() const
{
	m_backGround->Draw();
	DrawString(300, static_cast<int>(Game::kScreenHeight * 0.5f), "Title", 0x000000);
	m_fade.Draw();
}
