#include "ButtonReturnToTitle.h"
#include "Image.h"
#include "ScenePause.h"

namespace
{
	const std::string kImagePath = "ButtonReturnToTitle.png";
	const std::string kImagePassNoFocused = "ButtonReturnToTitle_NoFocused.png";
	constexpr float kButtonFocusExpand = 0.25f;
}

void ButtonReturnToTitle::FocusedUpdate()
{
	++m_frameTimer;
	m_image->SetExRate(2 + kButtonFocusExpand * abs(sinf(m_frameTimer * Calculation::kDegToRad * 3)));
}

void ButtonReturnToTitle::NormalUpdate()
{
	m_image->SetExRate(2.0f);
}

ButtonReturnToTitle::ButtonReturnToTitle(Vector2 initPos, ScenePause& parent) :
	Button(initPos),
	m_pauseSceneRef(parent),
	m_frameTimer(0)
{
	m_image = std::make_shared<Image>(kImagePassNoFocused);
	m_image->ExpandGraph(2.0f);
}

ButtonReturnToTitle::~ButtonReturnToTitle()
{
}

void ButtonReturnToTitle::OnFocused()
{
	InvertState();
	m_image->SetGraph(kImagePath);
}

void ButtonReturnToTitle::OnDisfocused()
{
	InvertState();
	m_image->SetGraph(kImagePassNoFocused);
}

void ButtonReturnToTitle::OnPressed()
{
	m_pauseSceneRef.ReturnToTitle();
}

void ButtonReturnToTitle::Draw() const
{
	m_image->Draw(m_pos);
}
