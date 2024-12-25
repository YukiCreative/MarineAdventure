#include "PauseScene.h"
#include "ScreenFade.h"
#include "BackGround.h"
#include "Camera.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"

PauseScene::PauseScene() :
	m_fade(ScreenFade::Getinstance())
{
	m_camera = std::make_shared<Camera>();
	m_back = std::make_shared<BackGround>(*m_camera, Vector2::Zero(), "Data/Image/Marine.jpg");
	m_back->SetImageBlendMode(DX_BLENDMODE_ALPHA, 128);
}

void PauseScene::NormalUpdate()
{
	Input& input = Input::GetInstance();
	if (input.IsTrigger("Pause"))
	{
		SceneController::GetInstance().RemoveSceme();
		return;
	}
}

void PauseScene::Draw() const
{
	m_back->Draw();
}
