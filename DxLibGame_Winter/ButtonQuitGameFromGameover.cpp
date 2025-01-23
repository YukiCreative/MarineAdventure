#include "ButtonQuitGameFromGameover.h"
#include "Image.h"
#include "SceneController.h"
#include "SceneGameover.h"
#include "Application.h"

namespace
{
	const std::string kImagePath = "ButtonQuitGame_Gameover.png";
	const std::string kNoFImagePath = "ButtonQuitGame_Gameover_NoF.png";

	constexpr float kBaseExRate = 1.0f;
	constexpr float kFocusedExRate = 1.5f;
}

void ButtonQuitGameFromGameover::FocusedUpdate()
{
	float exRate = std::lerp(m_image->ExRate(), kFocusedExRate, 0.2f);
	m_image->SetExRate(exRate);
}

void ButtonQuitGameFromGameover::NormalUpdate()
{
	float exRate = std::lerp(m_image->ExRate(), kBaseExRate, 0.2f);
	m_image->SetExRate(exRate);
}

ButtonQuitGameFromGameover::ButtonQuitGameFromGameover(const Vector2& initPos) :
	Button(initPos)
{
	m_image = std::make_shared<Image>(kNoFImagePath);
	m_image->SetExRate(kBaseExRate);
}

void ButtonQuitGameFromGameover::Draw() const
{
	m_image->Draw(m_pos);
}

void ButtonQuitGameFromGameover::OnFocused()
{
	InvertState();
	m_image->SetGraph(kImagePath);
}

void ButtonQuitGameFromGameover::OnDisfocused()
{
	InvertState();
	m_image->SetGraph(kNoFImagePath);
}

void ButtonQuitGameFromGameover::OnPressed()
{
	// ÉQÅ[ÉÄÇé~ÇﬂÇÈ
	Application::GetInstance().Quit();
}
