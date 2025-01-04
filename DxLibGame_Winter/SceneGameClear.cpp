#include "SceneGameClear.h"
#include "ScreenFade.h"
#include "BackGround.h"
#include "Camera.h"	
#include "Input.h"
#include "game.h"

namespace
{
	const std::string kImagePath = "Marine.jpg";
}

void SceneGameClear::NormalUpdate()
{
	Input& input = Input::GetInstance();

	m_camera->Update();
	m_back->Update();
	m_fade.Update();

	if (input.IsTrigger("ChangeScene_Debug"))
	{
		SceneChangeWithFadeOut("Title");
		return;
	}
}

SceneGameClear::SceneGameClear() :
	m_fade(ScreenFade::Getinstance())
{
	m_camera = std::make_shared<Camera>();
	m_back = std::make_shared<BackGround>(*m_camera, Vector2::Zero(), kImagePath);
}

void SceneGameClear::Draw() const
{
	m_back->Draw();
	DrawString(static_cast<int>(Game::kScreenHalfWidth), static_cast<int>(Game::kScreenHalfHeight), "GameClear!!!!!", 0xffffff);
	m_fade.Draw();
}

void SceneGameClear::Entry()
{
	m_fade.Fade(60, 0);
}
