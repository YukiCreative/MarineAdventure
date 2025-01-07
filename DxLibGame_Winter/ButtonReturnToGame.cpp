#include "ButtonReturnToGame.h"
#include "SceneController.h"
#include "Image.h"
#include <memory>
#include <string>
#include "Calculation.h"
#include "PauseScene.h"

namespace
{
	const std::string kImagePass = "ButtonReturnToGame.png";
	const std::string kNoFocusedImagePass = "ButtonReturnToGame_NoFocused.png";
}

void ButtonReturnToGame::FocusedUpdate()
{
	++m_frameCount;
	if (m_frameCount > 360) m_frameCount = 0;
	m_pos.x += cos(m_frameCount * Calculation::kDegToRad);
}

void ButtonReturnToGame::NormalUpdate()
{
}

ButtonReturnToGame::ButtonReturnToGame(Vector2 initPos, PauseScene& pauseScene) :
	Button(initPos),
	m_pauseSceneRef(pauseScene),
	m_frameCount(0)
{
	m_image = std::make_shared<Image>(kNoFocusedImagePass);
	m_image->ExpandGraph(2.0f);
}

ButtonReturnToGame::~ButtonReturnToGame()
{
}

void ButtonReturnToGame::OnFocused()
{
	InvertState();
	m_image->SetGraph(kImagePass);
}

void ButtonReturnToGame::OnDisfocused()
{
	InvertState();
	m_image->SetGraph(kNoFocusedImagePass);
}

void ButtonReturnToGame::OnPressed()
{
	// ポーズシーンを消す
	m_pauseSceneRef.ReturnToGame();
}

void ButtonReturnToGame::Draw() const
{
	m_image->Draw(m_pos);
}
