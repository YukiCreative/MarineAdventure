#include "ButtonQuitGame.h"
#include "Image.h"
#include "Application.h"

namespace
{
	const std::string kImageFileName = "ButtonQuitGame.png";
	constexpr float kBaseButtonExpand = 2.0f;
}

void ButtonQuitGame::FocusedUpdate()
{
	++m_frameCount;
	// 点滅とかさせたい
	m_image->SetExRate(kBaseButtonExpand + abs(sinf(m_frameCount * 0.05f)));
}

void ButtonQuitGame::NormalUpdate()
{
	m_image->SetExRate(1);
}

ButtonQuitGame::ButtonQuitGame(const Vector2& initPos) :
	Button(initPos),
	m_frameCount(0)
{
	m_image = std::make_shared<Image>(kImageFileName);
	m_image->SetExRate(kBaseButtonExpand);
}

void ButtonQuitGame::OnFocused()
{
	InvertState();
}

void ButtonQuitGame::OnDisfocused()
{
	InvertState();
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