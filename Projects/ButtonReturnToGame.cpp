#include "ButtonReturnToGame.h"
#include "SceneController.h"
#include "Image.h"
#include <memory>
#include <string>
#include "Calculation.h"
#include "ScenePause.h"
#include "game.h"

namespace
{
	const std::string kImagePath = "ButtonReturnToGame.png";
	const std::string kNoFocusedImagePass = "ButtonReturnToGame_NoFocused.png";

	// これかけるといい感じの周期になるんです
	constexpr float kCycleFactor = 0.05f;
	constexpr float kBaseButtonExpand = 1.0f;
	constexpr float kPlusExpandPoint = 0.5f;
}

void ButtonReturnToGame::FocusedUpdate()
{
	++m_frameCount;
	m_image->SetExRate(kBaseButtonExpand + abs(sinf(m_frameCount * kCycleFactor) * kPlusExpandPoint));
}

void ButtonReturnToGame::NormalUpdate()
{
}

ButtonReturnToGame::ButtonReturnToGame(Vector2 initPos, ScenePause& pauseScene) :
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
	m_image->SetGraph(kImagePath);
}

void ButtonReturnToGame::OnDisfocused()
{
	InvertState();
	m_image->SetGraph(kNoFocusedImagePass);
	m_image->SetExRate(kBaseButtonExpand);
	m_frameCount = 0;
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
