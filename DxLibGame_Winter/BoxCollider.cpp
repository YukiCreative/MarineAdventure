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

CollisionStatus BoxCollider::CheckHitCircle(CircleCollider& otherCircle)
{
    // ��`�̕ӂŁA�~�̒��S���W�ƈ�ԋ߂��_���o��
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(m_pos.x, Left(), Right());
    nearestPoint.y = std::clamp(m_pos.y, Top(), Bottom());

    // �o������_�̋������A�~�̔��a�ȉ��Ȃ瓖�����Ă���
    Vector2 distVec = m_pos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // �~�̔��a�̑傫���������AdistVec�̌����̃x�N�g������肽��
    Vector2 radiusVec = distVec.GetNormalize() * otherCircle.GetRadius();

    CollisionStatus result;
    result.isCollide = sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
    result.overlap = radiusVec - distVec;
    // ������̒��S���m���Ȃ����x�N�g�����ǂ�Ȍ������Ŕ���
    Vector2 pointDist = otherCircle.GetPos() - m_pos;
    float distDeg = std::atan2(pointDist.x, pointDist.y) * Calculation::kRadToDeg;
    // �͈͂�0~360�ɂ����Ă�������
    if (distDeg < 0) distDeg += 360;
    // �l�p�`�̒��S����E��̒��_�Ɍ������x�N�g���̊p�x
    // ��������ɂق���3�������o��
    Vector2 rectVec = Vector2(Right(), Bottom()) - m_pos;
    float rectDeg = std::atan2(rectVec.x, rectVec.y) * Calculation::kRadToDeg;
    if (distDeg > rectDeg && distDeg <= 180 - rectDeg) result.normal = Vector2::Down();
    if (distDeg > 180 - rectDeg && distDeg <= 180 + rectDeg) result.normal = Vector2::Left();
    if (distDeg > 180 + rectDeg && distDeg <= 360 - rectDeg) result.normal = Vector2::Up();
    if (distDeg > 360 - rectDeg || distDeg <= rectDeg) result.normal = Vector2::Right();

    return result;
}

CollisionStatus BoxCollider::CheckHitCircle(CircleCollider& otherCircle, Vector2 offset)
{
	return CollisionStatus();
}

CollisionStatus BoxCollider::CheckHitBox(BoxCollider& otherRect)
{
    CollisionStatus result;
	// �����̉E�[��葊��̍��[�̂ق����E���Ȃ�c���J��Ԃ�
    result.isCollide = 
        Right() < otherRect.Left() &&
        Left() > otherRect.Right() &&
        Top() > otherRect.Bottom() &&
        Bottom() < otherRect.Top();
    // �߂荞�݂Ɩ@���o���̖��������
    result.overlap = Vector2::Zero();
    result.normal = Vector2::Zero();

    return result;
}

CollisionStatus BoxCollider::CheckHitBox(BoxCollider& otherRect, Vector2 offset)
{
	return CollisionStatus();
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