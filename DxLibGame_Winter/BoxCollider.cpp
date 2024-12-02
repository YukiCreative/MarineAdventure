#include "BoxCollider.h"
#include "CircleCollider.h"
#include <algorithm>
#include <memory>
#include "Calculation.h"
#include "LineCollider.h"
#include <cassert>

BoxCollider::BoxCollider(Vector2& pos, float w, float h) :
	Collider(ColKind::kBox, pos),
	m_rectWidth(w),
	m_rectHeight(h)
{
    // ���S����̑��΋������o���Ă܂�
    Vector2 topLeft = m_pos - Vector2(Left(), Top());
    Vector2 bottomLeft = m_pos = Vector2(Left(), Bottom());
    Vector2 topRight = m_pos = Vector2(Right(), Top());
    Vector2 bottomRight = m_pos - Vector2(Right(), Bottom());
    // �e�ӂ�Collider��
    m_lines[0] = std::make_shared<LineCollider>(m_pos, topLeft, topRight);
    m_lines[1] = std::make_shared<LineCollider>(m_pos, topLeft, bottomLeft);
    m_lines[2] = std::make_shared<LineCollider>(m_pos, topRight, bottomRight);
    m_lines[3] = std::make_shared<LineCollider>(m_pos, bottomLeft, bottomRight);
}

CollisionStatus BoxCollider::CheckHitCircle(const CircleCollider& otherCircle) const
{
    CollisionStatus result;
    assert(false && "���߂��@�����ł��ĂȂ���");
    return result;
}

CollisionStatus BoxCollider::CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const
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

    CollisionStatus result;
    result.isCollide = sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
    result.overlap = radiusVec - distVec;

    return result;
}

CollisionStatus BoxCollider::CheckHitBox(const BoxCollider& otherRect) const 
{
    CollisionStatus result;
	// �����̉E�[��葊��̍��[�̂ق����E���Ȃ�c���J��Ԃ�
    result.isCollide = 
        Right() < otherRect.Left() &&
        Left() > otherRect.Right() &&
        Top() > otherRect.Bottom() &&
        Bottom() < otherRect.Top();
    // �߂荞�ݖ��������
    result.overlap = Vector2::Zero();

    return result;
}

CollisionStatus BoxCollider::CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const
{
    CollisionStatus result;
    // �����̉E�[��葊��̍��[�̂ق����E���Ȃ�c���J��Ԃ�
    result.isCollide =
        Right() + offset.x < otherRect.Left() &&
        Left() + offset.x > otherRect.Right() &&
        Top() + offset.y > otherRect.Bottom() &&
        Bottom() + offset.y < otherRect.Top();
    // �߂荞�ݖ��������
    result.overlap = Vector2::Zero();

    return result;
}

CollisionStatus BoxCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& offset, Vector2& crossPos) const
{
    assert(false && "���߂��@�����ł��ĂȂ���");
    return CollisionStatus();
}