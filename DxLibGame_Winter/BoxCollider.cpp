#include "BoxCollider.h"
#include "CircleCollider.h"
#include <algorithm>
#include <memory>
#include "Calculation.h"

BoxCollider::BoxCollider(Vector2& pos, float w, float h) :
	Collider(ColKind::kBox, pos),
	m_rectWidth(w),
	m_rectHeight(h)
{
}

bool BoxCollider::CheckHitCircle(CircleCollider& otherCircle) const
{
    Vector2 circlePos = otherCircle.GetPos();
    // ��`�̕ӂŁA�~�̒��S���W�ƈ�ԋ߂��_���o��
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(circlePos.x, Left(), Right());
    nearestPoint.y = std::clamp(circlePos.y, Top(), Bottom());

    // �o������_�̋������A�~�̔��a�ȉ��Ȃ瓖�����Ă���
    Vector2 distVec = circlePos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // �~�̔��a�̑傫���������AdistVec�̌����̃x�N�g������肽��
    Vector2 radiusVec = distVec.GetNormalize() * otherCircle.GetRadius();

    return sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
}

bool BoxCollider::CheckHitCircle(CircleCollider& otherCircle, const Vector2& offset) const
{
    // �߂�ǂ���������~�̕��������Ă���Ă��Ƃł����H
    Vector2 circlePos = otherCircle.GetPos() - offset;
    // ��`�̕ӂŁA�~�̒��S���W�ƈ�ԋ߂��_���o��
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(circlePos.x, Left(), Right());
    nearestPoint.y = std::clamp(circlePos.y, Top(), Bottom());

    // �o������_�̋������A�~�̔��a�ȉ��Ȃ瓖�����Ă���
    Vector2 distVec = circlePos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // �~�̔��a�̑傫���������AdistVec�̌����̃x�N�g������肽��
    Vector2 radiusVec = distVec.GetNormalize() * otherCircle.GetRadius();

    return sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
}

bool BoxCollider::CheckHitBox(BoxCollider& otherRect) const 
{
    // �����̉E�[��葊��̍��[�̂ق����E���Ȃ�c���J��Ԃ�
    return  Right() < otherRect.Left() &&
            Left() > otherRect.Right() &&
            Top() > otherRect.Bottom() &&
            Bottom() < otherRect.Top();
}

bool BoxCollider::CheckHitBox(BoxCollider& otherRect, const Vector2& offset) const
{
    // �����̉E�[��葊��̍��[�̂ق����E���Ȃ�c���J��Ԃ�
    return  Right() + offset.x < otherRect.Left() &&
            Left() + offset.x > otherRect.Right() &&
            Top() + offset.y > otherRect.Bottom() &&
            Bottom() + offset.y < otherRect.Top();
}

float BoxCollider::Right() const
{
	return m_pos.x + m_rectWidth * 0.5f;
}

float BoxCollider::Left() const
{
	return m_pos.x - m_rectWidth * 0.5f;
}

float BoxCollider::Top() const
{
	return m_pos.y - m_rectHeight * 0.5f;
}

float BoxCollider::Bottom() const 
{
	return m_pos.y + m_rectHeight * 0.5f;
}