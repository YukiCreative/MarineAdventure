#include "ButtonReturnToTitle.h"
#include "Image.h"
#include "PauseScene.h"

namespace
{
	const std::string kImagePass = "ButtonReturnToTitle.png";
	const std::string kImagePassNoFocused = "ButtonReturnToTitle_NoFocused.png";
}

void ButtonReturnToTitle::FocusedUpdate()
{
	++m_frameTimer;
	m_image->RotateGraph(1);
}

void ButtonReturnToTitle::NormalUpdate()
{
	m_image->SetAngle(0);
}

ButtonReturnToTitle::ButtonReturnToTitle(Vector2 initPos, PauseScene& parent) :
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
	m_image->SetGraph(kImagePass);
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
