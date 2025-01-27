#include "ButtonGameStart.h"
#include "SceneController.h"
#include "SceneTitle.h"
#include "SoundManager.h"
#include <memory>
#include "Image.h"

namespace
{
	const std::string kImagePath          = "ButtonStartGame.png";
	const std::string kNoFocusedImagePath = "ButtonStartGame_NoFocused.png";
	const std::string kStartSound = "キラキラ効果音.mp3";
	constexpr float kBaseButtonExpand = 1.0f;
	// Base + Plus = MaxExRate
	constexpr float kPlusExpandPoint = 0.5f;
}

ButtonGameStart::ButtonGameStart(Vector2 initPos, SceneTitle& title) :
	Button(initPos),
	m_frameCount(0),
	m_titleRef(title)
{
	m_image = std::make_shared<Image>(kNoFocusedImagePath);
	m_image->SetExRate(kBaseButtonExpand);
}

void ButtonGameStart::OnFocused()
{
	InvertState();
	m_image->SetGraph(kImagePath);
}

void ButtonGameStart::OnDisfocused()
{
	InvertState();
	m_frameCount = 0;
	m_image->SetGraph(kNoFocusedImagePath);
}

void ButtonGameStart::NormalUpdate()
{
	m_image->SetExRate(kBaseButtonExpand);
}

void ButtonGameStart::FocusedUpdate()
{
	++m_frameCount;
	// 点滅とかさせたい
	m_image->SetExRate(kBaseButtonExpand + abs(sinf(m_frameCount * 0.05f) * kPlusExpandPoint));
}

void ButtonGameStart::OnPressed()
{
	// シーン遷移をお願い
	m_titleRef.GameStart();
	SoundManager::GetInstance().Play(kStartSound);
	m_frameCount = 0;
}

void ButtonGameStart::Draw() const
{
	// UIだしスクリーン座標で描いてもいいよね？
	m_image->Draw(m_pos);
}
