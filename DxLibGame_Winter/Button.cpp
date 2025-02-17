#include "Button.h"

void Button::InvertState()
{
	if (m_updateState == &Button::FocusedUpdate)
	{
		m_updateState = &Button::NormalUpdate;
	}
	else
	{
		m_updateState = &Button::FocusedUpdate;
	}
}

Button::Button(Vector2 initPos) :
	GameObject(initPos),
	m_updateState(&Button::NormalUpdate),
	m_downButton(this),
	m_leftButton(this),
	m_rightButton(this),
	m_upButton(this)
{
}

void Button::Update()
{
	// ‚¢‚Â‚à‚Ì
	(this->*m_updateState)();
}