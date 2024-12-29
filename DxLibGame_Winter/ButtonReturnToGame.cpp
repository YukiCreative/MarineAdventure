#include "ButtonReturnToGame.h"
#include "SceneController.h"
#include "Image.h"
#include <memory>
#include <string>
#include "Calculation.h"
#include "PauseScene.h"

namespace
{
	const std::string kImagePass = "Data/Image/GameStartButton.png";
}

void ButtonReturnToGame::FocusedUpdate()
{
	++m_frameCount;
	if (m_frameCount > 360) m_frameCount = 0;
	m_pos += sin(m_frameCount * Calculation::kDegToRad);
}

void ButtonReturnToGame::NormalUpdate()
{
}

ButtonReturnToGame::ButtonReturnToGame(Vector2 initPos, PauseScene& pauseScene) :
	Button(initPos),
	m_pauseSceneRef(pauseScene),
	m_frameCount(0)
{
	m_image = std::make_shared<Image>(kImagePass);
}

void ButtonReturnToGame::OnPressed()
{
	// ポーズシーンを消す
	m_pauseSceneRef.RetrunToGame();
}

void ButtonReturnToGame::Draw() const
{
	m_image->Draw(m_pos);
}
