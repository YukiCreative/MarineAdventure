#include "SceneTitle.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"
#include <cassert>
#include "game.h"
#include <memory>
#include "BackGround.h"
#include "Camera.h"

#include "TestScene.h"

namespace
{
	const Vector2 kScreenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
}

SceneTitle::SceneTitle()
{
	m_camera = std::make_shared<Camera>();
	// ƒ^ƒCƒgƒ‹‰æ‘œ‚ğƒ[ƒh
	m_backGround = std::make_shared<BackGround>(*m_camera, kScreenMiddlePoint, "Data/Image/ŠC”wŒi.jpg");
	m_backGround->ExpandGtaph(2.2f);
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Update()
{
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
}
