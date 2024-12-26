#include "Button.h"

Button::Button(Vector2 initPos) :
	GameObject(initPos),
	m_updateState(&Button::NormalUpdate)
{
}

void Button::Update()
{
	// ������
	(this->*m_updateState)();
}

void Button::OnForcused()
{
	// ��Ԃ�ς���
	m_updateState = &Button::ForcusedUpdate;
}
