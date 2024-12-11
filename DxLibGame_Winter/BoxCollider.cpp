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
    Vector2 topLeft =  Vector2(Left(), Top()) - m_pos;
    Vector2 bottomLeft =  Vector2(Left(), Bottom()) - m_pos;
    Vector2 topRight = Vector2(Right(), Top()) - m_pos;
    Vector2 bottomRight = Vector2(Right(), Bottom()) - m_pos;
    // �e�ӂ�Collider��
    m_lines[static_cast<int>(LineDir::Top)] = std::make_shared<LineCollider>(m_pos, topLeft, topRight); // ��
    m_lines[static_cast<int>(LineDir::Left)] = std::make_shared<LineCollider>(m_pos, topLeft, bottomLeft); // ��
    m_lines[static_cast<int>(LineDir::Right)] = std::make_shared<LineCollider>(m_pos, bottomRight, topRight); // �E
    m_lines[static_cast<int>(LineDir::Bottom)] = std::make_shared<LineCollider>(m_pos, bottomRight, bottomLeft); // ��
    
    for (auto& isValid : m_validLineCol)
    {
        isValid = true;
    }
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

CollisionStatus BoxCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& offset) const
{
    assert(false && "���߂��@�����ł��ĂȂ���");
    return CollisionStatus();
}