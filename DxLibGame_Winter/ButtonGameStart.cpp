#include "ButtonGameStart.h"
#include "SceneController.h"
#include "SceneTitle.h"
#include <memory>
#include "Image.h"

ButtonGameStart::ButtonGameStart(Vector2 initPos, SceneTitle& title) :
	Button(initPos),
	m_frameCount(0),
	m_text("GameStart!!"),
	m_titleRef(title)
{
	m_image = std::make_shared<Image>("Data/Image/GameStartButton.png");
}
void ButtonGameStart::NormalUpdate()
{
	// 何もしない
}

void ButtonGameStart::ForcusedUpdate()
{
	++m_frameCount;
	// 点滅とかさせたい
	m_image->SetExRate(sinf(m_frameCount * 0.1f) * 1.5f);
}

void ButtonGameStart::Onpressed()
{
	// シーン遷移をシーンにお願い
	m_titleRef.GameStart();
}

void ButtonGameStart::Draw() const
{
	// UIだしスクリーン座標で描いてもいいよね？
	m_image->Draw(m_pos);
}
