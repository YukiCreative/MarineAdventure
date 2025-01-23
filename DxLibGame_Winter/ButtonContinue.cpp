#include "ButtonContinue.h"
#include "Image.h"
#include "SceneController.h"
#include "SceneGameover.h"

namespace
{
	const std::string kImagePath = "ButtonContinue.png";
	const std::string kNoFImagePath = "ButtonContinue_NoF.png";

	constexpr float kBaseExRate = 1.0f;
	constexpr float kFocusedExRate = 1.5f;
}

void ButtonContinue::FocusedUpdate()
{
	float exRate = std::lerp(m_image->ExRate(), kFocusedExRate, 0.2f);
	m_image->SetExRate(exRate);
}

void ButtonContinue::NormalUpdate()
{
	float exRate = std::lerp(m_image->ExRate(), kBaseExRate, 0.2f);
	m_image->SetExRate(exRate);
}

ButtonContinue::ButtonContinue(const Vector2& initPos) :
	Button(initPos)
{
	m_image = std::make_shared<Image>(kNoFImagePath);
	m_image->SetExRate(kBaseExRate);
}

void ButtonContinue::Draw() const
{
	m_image->Draw(m_pos);
}

void ButtonContinue::OnFocused()
{
	InvertState();
	m_image->SetGraph(kImagePath);
}

void ButtonContinue::OnDisfocused()
{
	InvertState();
	m_image->SetGraph(kNoFImagePath);
}

void ButtonContinue::OnPressed()
{
	// ƒQ[ƒ€ƒV[ƒ“‚É–ß‚é
	std::static_pointer_cast<SceneGameover>(SceneController::GetInstance().CurrentScene())->ReturnToGame();
}
