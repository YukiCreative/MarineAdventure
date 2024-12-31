#include "PauseScene.h"
#include "ScreenFade.h"
#include "BackGround.h"
#include "Camera.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"
#include "game.h"
#include "ButtonSystem.h"
#include "ButtonReturnToTitle.h"
#include "ButtonReturnToGame.h"

namespace 
{
	const Vector2 kScrrenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	const Vector2 kPosButtonReturnToTitle = kScrrenMiddlePoint;
	const Vector2 kPosButtonReturnToGame = (kScrrenMiddlePoint - Vector2(0, 80));
}

PauseScene::PauseScene()
{
	m_camera = std::make_shared<Camera>();
	m_back = std::make_shared<BackGround>(*m_camera, Vector2::Zero(), "Data/Image/Marine.jpg");

	// É{É^ÉìÇÃê›íË
	m_buttonSystem = std::make_shared<ButtonSystem>();
	std::shared_ptr<ButtonReturnToTitle> returnTitleButton = std::make_shared<ButtonReturnToTitle>(kPosButtonReturnToTitle, *this);
	std::shared_ptr<ButtonReturnToGame> returnGameButton = std::make_shared<ButtonReturnToGame>(kPosButtonReturnToGame, *this);
	returnGameButton->SetDownButton(returnTitleButton);
	returnGameButton->SetUpButton(returnTitleButton);
	returnTitleButton->SetUpButton(returnGameButton);
	returnTitleButton->SetDownButton(returnGameButton);
	m_buttonSystem->AddButton(returnTitleButton);
	m_buttonSystem->AddButton(returnGameButton);
	m_buttonSystem->SetButtonFocus(returnTitleButton);
}

void PauseScene::Entry()
{
	m_fade.Fade(30, 0);
}

void PauseScene::NormalUpdate()
{
	m_camera->Update();
	m_buttonSystem->Update();
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
	m_buttonSystem->Draw();
	m_fade.Draw();
}

void PauseScene::ReturnToTitle()
{
	m_fade.SetColor(0x000000);
	SceneRemoveWithFadeOut();
	//SceneChangeWithFadeOut("Title");
}

void PauseScene::RetrunToGame()
{
	SceneRemoveWithFadeOut();
}