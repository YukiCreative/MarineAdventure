#include "SceneGameClear.h"
#include "ScreenFade.h"
#include "BackGround.h"
#include "Camera.h"	
#include "Input.h"

namespace
{
	const std::string kImagePath = "Marine.png";
}

void SceneGameClear::NormalUpdate()
{
	Input& input = Input::GetInstance();

	m_camera->Update();
	m_back->Update();

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
}

void SceneGameClear::Entry()
{
	m_fade.Fade(60, 0);
}
