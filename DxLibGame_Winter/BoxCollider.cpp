#include "BoxCollider.h"
#include "CircleCollider.h"
#include <algorithm>
#include <memory>

BoxCollider::BoxCollider(Vector2& pos, float w, float h) :
	Collider(ColKind::kBox, pos),
	m_rectWidth(w),
	m_rectHeight(h)
{
}

bool BoxCollider::CheckHit(CircleCollider& otherCircle)
{
	Vector2 circlePos = otherCircle.GetPos();
	// ��`�̕ӂŁA�~�̒��S���W�ƈ�ԋ߂��_���o��
	Vector2 nearestPoint;
	nearestPoint.x = std::clamp(circlePos.x, Left(), Right());
	nearestPoint.y = std::clamp(circlePos.y, Top(), Bottom());

	// �o������_�̋������A�~�̔��a�ȉ��Ȃ瓖�����Ă���
	float distance = (circlePos - nearestPoint).SqrMagnitude();
	return distance <= otherCircle.GetRadius() * otherCircle.GetRadius();
}

bool BoxCollider::CheckHit(BoxCollider& otherRect)
{
	// �����̉E�[��葊��̍��[�̂ق����E���Ȃ�c���J��Ԃ�
	if (Right() < otherRect.Left()) return false;
	if (Left() > otherRect.Right()) return false;
	if (Top() > otherRect.Bottom()) return false; 
	if (Bottom() < otherRect.Top()) return false;
	// �����܂ł���Γ������Ă���
	return true;
}

float BoxCollider::Right()
{
	return m_pos.x + m_rectWidth * 0.5f;
}

float BoxCollider::Left()
{
	return m_pos.x - m_rectWidth * 0.5f;
}

float BoxCollider::Top()
{
	return m_pos.y - m_rectHeight * 0.5f;
}

float BoxCollider::Bottom()
{
	return m_pos.y + m_rectHeight * 0.5f;
}