#include "PauseScene.h"
#include "ScreenFade.h"
#include "BackGround.h"
#include "Camera.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"
#include "game.h"

namespace 
{
	const Vector2 kScrrenModdlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
}

PauseScene::PauseScene()
{
	m_camera = std::make_shared<Camera>();
	m_back = std::make_shared<BackGround>(*m_camera, Vector2::Zero(), "Data/Image/Marine.jpg");
	m_fade.Fade(30, 0);
}

void PauseScene::NormalUpdate()
{
	m_camera->Update();
	m_fade.Update();
	Input& input = Input::GetInstance();
	if (input.IsTrigger("Pause"))
	{
		SceneStackWithFadeOut("Game", 30);
		return;
	}
}

void PauseScene::Draw() const
{
	m_back->Draw();
	m_fade.Draw();
}
