#include "Button.h"

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

void Button::OnForcused()
{
	// ó‘Ô‚ğ•Ï‚¦‚é
	m_updateState = &Button::ForcusedUpdate;
}

void Button::OnDisfocused()
{
	// ó‘Ô‚ğ•Ï‚¦‚é
	m_updateState = &Button::NormalUpdate;
}