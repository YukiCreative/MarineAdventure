#include "ButtonContinue.h"
#include "Image.h"
#include "SceneController.h"
#include "SceneGameover.h"
#include "SoundManager.h"

namespace
{
	const std::string kImagePath = "ButtonContinue.png";
	const std::string kNoFImagePath = "ButtonContinue_NoF.png";

	const std::string kPushedSound = "システム決定音_11_3.mp3";

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
	// ゲームシーンに戻る
	SoundManager::GetInstance().Play(kPushedSound);
	std::static_pointer_cast<SceneGameover>(SceneController::GetInstance().CurrentScene())->ReturnToGame();
}

void ButtonContinue::SetBlendingMode(const int& mode, const int& param)
{
	m_image->SetImageBlendMode(mode, param);
}
