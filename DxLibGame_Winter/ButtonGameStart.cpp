#include "ButtonGameStart.h"
#include "SceneController.h"
#include "SceneTitle.h"
#include <memory>
#include "Image.h"

namespace
{
	const std::string kImagePath = "GameStartButton.png";
	constexpr float kBaseButtonExpand = 2.0f;
}

ButtonGameStart::ButtonGameStart(Vector2 initPos, SceneTitle& title) :
	Button(initPos),
	m_frameCount(0),
	m_titleRef(title)
{
	m_image = std::make_shared<Image>(kImagePath);
	m_image->SetExRate(kBaseButtonExpand);
}

void ButtonGameStart::OnFocused()
{
	InvertState();
}

void ButtonGameStart::OnDisfocused()
{
	InvertState();
}

void ButtonGameStart::NormalUpdate()
{
	m_image->SetExRate(1);
}

void ButtonGameStart::FocusedUpdate()
{
	++m_frameCount;
	// 点滅とかさせたい
	m_image->SetExRate(kBaseButtonExpand + abs(sinf(m_frameCount * 0.05f)));
}

void ButtonGameStart::OnPressed()
{
	// シーン遷移をお願い
	m_titleRef.GameStart();
}

void ButtonGameStart::Draw() const
{
	// UIだしスクリーン座標で描いてもいいよね？
	m_image->Draw(m_pos);
}
