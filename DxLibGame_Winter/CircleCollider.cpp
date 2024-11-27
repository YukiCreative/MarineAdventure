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

CollisionStatus CircleCollider::CheckHitCircle(CircleCollider& otherCircle) const 
{
    // �~�`�Ɖ~�`�̓����蔻��
    // �����Ɠ�̉~�̍��v���a���ׂ�
    Vector2 distVec = m_pos - otherCircle.GetPos();
    float dist = distVec.SqrMagnitude();
    float radiusLength = m_radius + otherCircle.GetRadius();
    Vector2 distUnit = distVec.GetNormalize();
    Vector2 radiusVec =  distUnit * radiusLength;

    CollisionStatus result;
    result.isCollide = dist <= radiusLength * radiusLength;
    result.overlap = radiusVec - distVec;

    return result;
}

CollisionStatus CircleCollider::CheckHitCircle(CircleCollider& otherCircle, const Vector2& offset) const
{
    // �����̈ʒu��␳���݂ōl���� ���Ƃ͈ꏏ
    Vector2 distVec = m_pos - otherCircle.GetPos() + offset;
    float dist = distVec.SqrMagnitude();
    float radiusLength = m_radius + otherCircle.GetRadius();
    Vector2 distUnit = distVec.GetNormalize();
    Vector2 radiusVec = distUnit * radiusLength;

    CollisionStatus result;
    result.isCollide = dist <= radiusLength;
    result.overlap = radiusVec - distVec;

    return result;
}

CollisionStatus CircleCollider::CheckHitBox(BoxCollider& otherRect) const
{
    // ��`�̕ӂŁA�~�̒��S���W�ƈ�ԋ߂��_���o��
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(m_pos.x, otherRect.Left(), otherRect.Right());
    nearestPoint.y = std::clamp(m_pos.y, otherRect.Top(), otherRect.Bottom());
    // �~�̒��S�����S�ɂ߂荞��ł�����A���������ɍs������
    
    
    // �o������_�̋������A�~�̔��a�ȉ��Ȃ瓖�����Ă���
    Vector2 distVec = m_pos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // �~�̔��a�̑傫���������AdistVec�̌����̃x�N�g������肽��
    Vector2 radiusVec = distVec.GetNormalize() * m_radius;

    CollisionStatus result;
    result.isCollide = sqrDist <= m_radius * m_radius;
    result.overlap = radiusVec - distVec;

    return result;
}

CollisionStatus CircleCollider::CheckHitBox(BoxCollider& otherRect, const Vector2& offset) const
{
    // �␳
    Vector2 futurePos = m_pos + offset;
    // ��`�̎l����ϐ��ɂ��Ă���
    float rLeft = otherRect.Left();
    float rRight = otherRect.Right();
    float rTop = otherRect.Top();
    float rBottom = otherRect.Bottom();
    // ��`�̕ӂŁA���̉~�̒��S���W�ƈ�ԋ߂��_���o��(���i�K�ŁA�߂荞��ł��Ȃ����Ƃ��肤)
    Vector2 nowNearestPoint;
    nowNearestPoint.x = std::clamp(m_pos.x, rLeft, rRight);
    nowNearestPoint.y = std::clamp(m_pos.y, rTop, rBottom);
    Vector2 futureNearestPoint;
    futureNearestPoint.x = std::clamp(futurePos.x, rLeft, rRight);
    futureNearestPoint.y = std::clamp(futurePos.y, rTop, rBottom);

    // �o�����ړ���̂ƍŋߖT�_�̋������A�~�̔��a�ȉ��Ȃ瓖�����Ă���
    Vector2 distVec = futurePos - futureNearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // �ړ��O�̍ŋߖT�_����ړ���̒��S�֐L�΂����x�N�g��
    Vector2 overlapVec = nowNearestPoint - futurePos;
    // ���̌����ɉ~�̔��a�̕��𑫂�
    overlapVec += overlapVec.GetNormalize() * m_radius;

    CollisionStatus result;
    result.isCollide = sqrDist <= m_radius * m_radius;
    result.overlap = overlapVec;

    return result;
}
