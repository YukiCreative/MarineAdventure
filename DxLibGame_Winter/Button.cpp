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
	// ������
	(this->*m_updateState)();
}

void Button::OnForcused()
{
	// ��Ԃ�ς���
	m_updateState = &Button::ForcusedUpdate;
}

void Button::OnDisfocused()
{
	// ��Ԃ�ς���
	m_updateState = &Button::NormalUpdate;
}