#include "BoxCollider.h"
#include "CircleCollider.h"

BoxCollider::BoxCollider(Vector2& pos, float h, float v) :
	Collider(pos),
	m_rectHorizontalLength(h),
	m_rectVerticalLength(v)
{
}

bool BoxCollider::CheckHit(CircleCollider& other)
{
	return false;
}

bool BoxCollider::CheckHit(BoxCollider& other)
{
	// �����̉E�[��葊��̍��[�̂ق����E���Ȃ�c���J��Ԃ�
	if (Right() < other.Left()) return false;
	if (Left() > other.Right()) return false;
	if (Top() > other.Bottom()) return false; 
	if (Bottom() < other.Top()) return false;
	// �����܂ł���Γ������Ă���
	return true;
}

float BoxCollider::Right()
{
	return m_pos.x + m_rectHorizontalLength * 0.5f;
}

float BoxCollider::Left()
{
	return m_pos.x - m_rectHorizontalLength * 0.5f;
}

float BoxCollider::Top()
{
	return m_pos.y - m_rectVerticalLength * 0.5f;
}

float BoxCollider::Bottom()
{
	return m_pos.y + m_rectVerticalLength * 0.5f;
}