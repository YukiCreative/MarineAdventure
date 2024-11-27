#include "CircleCollider.h"
#include "BoxCollider.h"
#include <algorithm>
#include <cmath>
#include "Calculation.h"
#include <DxLib.h>

CircleCollider::CircleCollider(Vector2& pos, float radius) :
    Collider(ColKind::kCircle, pos),
    m_radius(radius)
{
}

bool CircleCollider::CheckHitCircle(CircleCollider& otherCircle) const 
{
    // �~�`�Ɖ~�`�̓����蔻��
    // �����Ɠ�̉~�̍��v���a���ׂ�
    Vector2 distVec = m_pos - otherCircle.GetPos();
    float dist = distVec.SqrMagnitude();
    float radiusLength = m_radius + otherCircle.GetRadius();
    return dist <= radiusLength * radiusLength;
}

bool CircleCollider::CheckHitCircle(CircleCollider& otherCircle, const Vector2& offset) const
{
    // �����̈ʒu��␳���݂ōl���� ���Ƃ͈ꏏ
    Vector2 distVec = m_pos - otherCircle.GetPos() + offset;
    float dist = distVec.SqrMagnitude();
    float radiusLength = m_radius + otherCircle.GetRadius();

    return dist <= radiusLength * radiusLength;
}

bool CircleCollider::CheckHitBox(BoxCollider& otherRect) const
{
    // ��`�̕ӂŁA�~�̒��S���W�ƈ�ԋ߂��_���o��
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(m_pos.x, otherRect.Left(), otherRect.Right());
    nearestPoint.y = std::clamp(m_pos.y, otherRect.Top(), otherRect.Bottom());
    
    // �o������_�̋������A�~�̔��a�ȉ��Ȃ瓖�����Ă���
    Vector2 distVec = m_pos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // �~�̔��a�̑傫���������AdistVec�̌����̃x�N�g������肽��
    Vector2 radiusVec = distVec.GetNormalize() * m_radius;

    return sqrDist <= m_radius * m_radius;
}

bool CircleCollider::CheckHitBox(BoxCollider& otherRect, const Vector2& offset) const
{   
    // ������Box�ł����������ς���Α��v
    CircleCollider circle = *this;
    BoxCollider box = otherRect;
    // �~�̕␳
    Vector2 futurePos = circle.GetPos() + offset;
    // �l�p�`�̊e���_���x�N�g����
    Vector2 rVertexTopRight(box.Right(), box.Top());
    Vector2 rVertexTopLeft(box.Left(), box.Top());
    Vector2 rVertexBottomRight(box.Right(), box.Bottom());
    Vector2 rVertexBottomLeft(box.Left(), box.Bottom());
    // �ړ��x�N�g�����A�l�p�`�̕ӂɓ������Ă��邩�`�F�b�N
    bool isHit = !Segment_Segment_MinLength(circle.GetPos(), futurePos, rVertexTopLeft, rVertexBottomLeft);
    isHit &= !Segment_Segment_MinLength(circle.GetPos(), futurePos, rVertexBottomLeft, rVertexBottomRight);
    isHit &= !Segment_Segment_MinLength(circle.GetPos(), futurePos, rVertexTopLeft, rVertexTopRight);
    isHit &= !Segment_Segment_MinLength(circle.GetPos(), futurePos, rVertexBottomRight, rVertexTopRight);

    return isHit;
}
