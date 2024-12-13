#include "SceneGameover.h"
#include <DxLib.h>
#include <memory>
#include "BackGround.h"
#include "Input.h"
#include "SceneController.h"
#include "SceneTitle.h"
#include "game.h"

SceneGameover::SceneGameover()
{
	m_gameoverBack = std::make_shared<BackGround>("Data/Image/GAMEOVER_Test.jpg");
}

void SceneGameover::Update()
{
	if (Input::GetInstance().IsTrigger("ChangeScene_Debug"))
	{
		// シーンが次のシーンをインクルードするのはどうかと思ってる
		// 別に今何かをしようってわけではない
		SceneController::GetInstance().ChangeScene(std::make_shared<SceneTitle>());
		return;
	}

	UpdateScreenEffect();
}

void SceneGameover::Draw() const
{
	m_gameoverBack->Draw();

	DrawString(static_cast<int>(Game::kScreenWidth * 0.5f), static_cast<int>(Game::kScreenHeight * 0.5f), "GameoverScene", 0xffffff);

	DrawScreenEffect();
}
