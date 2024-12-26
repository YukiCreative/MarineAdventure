#include "Button.h"

Button::Button(Vector2 initPos) :
	GameObject(initPos),
	m_updateState(&Button::NormalUpdate)
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
