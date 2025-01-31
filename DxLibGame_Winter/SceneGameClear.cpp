#include "SceneGameClear.h"
#include "ScreenFade.h"
#include "ImageObject.h"
#include "Camera.h"	
#include "Input.h"
#include "game.h"
#include "ButtonSystem.h"
#include "ButtonReturnToTitle.h"

namespace
{
	const std::string kImagePath = "Marine.jpg";
	const std::string kTextPath = "Clear.png";
}

void SceneGameClear::NormalUpdate()
{
	Input& input = Input::GetInstance();

	m_camera->Update();
	m_back->Update();
	m_fade.Update();

#if _DEBUG
	if (input.IsTrigger("ChangeScene_Debug"))
	{
		SceneChangeWithFadeOut("Title");
		return;
	}
#endif
}

void SceneGameClear::Init()
{
	m_back = std::make_shared<ImageObject>(*m_camera, Vector2::Zero(), kImagePath);
	m_clearText = std::make_shared<ImageObject>(*m_camera, Vector2::Zero(), kTextPath);

	// É{É^ÉìÇÃê›íË
	m_buttonSystem = std::make_shared<ButtonSystem>();
	std::shared_ptr<ButtonReturnToTitle> button = std::make_shared<ButtonReturnToTitle>(Vector2(0,0));
	m_buttonSystem->AddButton(button);
	m_buttonSystem->SetButtonFocus(button);
}

void SceneGameClear::Draw() const
{
	m_back->Draw();
	m_clearText->Draw();
	m_fade.Draw();
}

void SceneGameClear::Entry()
{
	m_fade.Fade(60, 0);
}
