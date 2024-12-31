#include "ButtonReturnToTitle.h"
#include "Image.h"
#include "PauseScene.h"

namespace
{
	const std::string kImagePass = "Data/Image/ButtonReturnToTitle.png";
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
	// ‚Æ‚è‚ ‚¦‚¸‚Ë
	m_image = std::make_shared<Image>(kImagePass);
}

ButtonReturnToTitle::~ButtonReturnToTitle()
{
}

void ButtonReturnToTitle::OnPressed()
{
	m_pauseSceneRef.ReturnToTitle();
}

void ButtonReturnToTitle::Draw() const
{
	m_image->Draw(m_pos);
}
