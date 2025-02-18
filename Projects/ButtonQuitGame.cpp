#include "ButtonQuitGame.h"
#include "Image.h"
#include "Application.h"

namespace
{
	const std::string kImageFileName          = "ButtonQuitGame.png";
	const std::string kNoFocusedImageFileName = "ButtonQuitGame_NoFocused.png";
	constexpr float kBaseButtonExpand         = 1.0f;
	constexpr float kPlusExRate               = 0.5f;
}

void ButtonQuitGame::FocusedUpdate()
{
	++m_frameCount;
	// 点滅とかさせたい
	m_image->SetExRate(kBaseButtonExpand + abs(sinf(m_frameCount * 0.05f) * kPlusExRate));
}

void ButtonQuitGame::NormalUpdate()
{
	m_image->SetExRate(kBaseButtonExpand);
}

ButtonQuitGame::ButtonQuitGame(const Vector2& initPos) :
	Button(initPos),
	m_frameCount(0)
{
	m_image = std::make_shared<Image>(kNoFocusedImageFileName);
	m_image->SetExRate(kBaseButtonExpand);
}

void ButtonQuitGame::OnFocused()
{
	InvertState();
	m_image->SetGraph(kImageFileName);
}

void ButtonQuitGame::OnDisfocused()
{
	InvertState();
	m_image->SetGraph(kNoFocusedImageFileName);
	m_frameCount = 0;
}

void ButtonQuitGame::OnPressed()
{
	// 今のままだとブチっと終わる
	Application::GetInstance().Quit();
}

void ButtonQuitGame::Draw() const
{
	m_image->Draw(m_pos);
}