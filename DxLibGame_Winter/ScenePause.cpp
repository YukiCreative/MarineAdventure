#include "ScenePause.h"
#include "ScreenFade.h"
#include "ImageObject.h"
#include "Camera.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"
#include "game.h"
#include "ButtonSystem.h"
#include "ButtonReturnToTitle.h"
#include "ButtonReturnToGame.h"
#include "Music.h"
#include "Statistics.h"
#include "SoundManager.h"

namespace 
{
	const Vector2 kScrrenMiddlePoint(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	const Vector2 kPosButtonReturnToTitle = kScrrenMiddlePoint + Vector2(0, 90);
	const Vector2 kPosButtonReturnToGame = (kScrrenMiddlePoint + Vector2(0, -90));
	const std::string kBackGroundPath = "Marine.jpg";

	const std::string kReturnGameSound = "èÍñ ì]ä∑éûÇÃå¯â âπ_3.mp3";

	constexpr int kPauseMusicVolume = 200;
	constexpr int kDefaultMusicVolume = 255;
}

ScenePause::~ScenePause()
{
	Music::GetInstance().SetVolume(kDefaultMusicVolume);
}

void ScenePause::Init()
{
	m_back = std::make_shared<ImageObject>(*m_camera, Vector2::Zero(), kBackGroundPath);

	// É{É^ÉìÇÃê›íË
	m_buttonSystem = std::make_shared<ButtonSystem>();

	std::shared_ptr<ButtonReturnToTitle> returnTitleButton = std::make_shared<ButtonReturnToTitle>(kPosButtonReturnToTitle);
	std::shared_ptr<ButtonReturnToGame>  returnGameButton = std::make_shared<ButtonReturnToGame>(kPosButtonReturnToGame, *this);

	returnGameButton->SetDownButton(returnTitleButton);
	returnGameButton->SetUpButton(returnTitleButton);
	returnTitleButton->SetUpButton(returnGameButton);
	returnTitleButton->SetDownButton(returnGameButton);

	m_buttonSystem->AddButton(returnTitleButton);
	m_buttonSystem->AddButton(returnGameButton);

	m_buttonSystem->SetButtonFocus(returnGameButton);
}

void ScenePause::Entry()
{
	Music::GetInstance().SetVolume(kPauseMusicVolume);
	m_fade.Fade(30, 0);
}

void ScenePause::NormalUpdate()
{
	m_camera->Update();
	m_buttonSystem->Update();
	m_fade.Update();
	Input& input = Input::GetInstance();
	if (input.IsTrigger("Pause"))
	{
		ReturnToGame();
		return;
	}
}

void ScenePause::Draw() const
{
	m_back->Draw();
	m_buttonSystem->Draw();
	m_fade.Draw();
}

void ScenePause::ReturnToTitle()
{
	Statistics::GetInstance().ResetNowStageScore();
	m_fade.SetColor(0x000000);
	SceneResumeWithFadeOut("Title");
}

void ScenePause::ReturnToGame()
{
	SoundManager::GetInstance().Play(kReturnGameSound);
	SceneRemoveWithFadeOut();
}