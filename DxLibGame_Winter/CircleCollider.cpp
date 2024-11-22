#include "CircleCollider.h"
#include "BoxCollider.h"
#include <algorithm>
#include <cmath>
#include "Calculation.h"

CircleCollider::CircleCollider(Vector2& pos, float radius) :
    Collider(ColKind::kCircle, pos),
    m_radius(radius)
{
}

CollisionStatus CircleCollider::CheckHitCircle(CircleCollider& otherCircle)
{
    // �~�`�Ɖ~�`�̓����蔻��
    // �����Ɠ�̉~�̍��v���a���ׂ�
    Vector2 distVec = m_pos - otherCircle.GetPos();
    float dist = distVec.SqrMagnitude();
    float radiusLength = m_radius + otherCircle.GetRadius();
    Vector2 distUnit = distVec.GetNormalize();
    Vector2 radiusVec =  distUnit * radiusLength;

    CollisionStatus result;
    result.isCollide = dist <= radiusLength;
    result.overlap = radiusVec - distVec;
    result.normal = -distUnit;

    return result;
}

CollisionStatus CircleCollider::CheckHitCircle(CircleCollider& otherCircle, Vector2 offset)
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
    result.normal = -distUnit;

    return result;
}

CollisionStatus CircleCollider::CheckHitBox(BoxCollider& otherRect)
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

    CollisionStatus result;
    result.isCollide = sqrDist <= m_radius * m_radius;
    result.overlap = radiusVec - distVec;
    // ������̒��S���m���Ȃ����x�N�g�����ǂ�Ȍ������Ŕ���
    // ����㉺�t�ɂȂ���
    Vector2 pointDist = m_pos - otherRect.GetPos();
    float distDeg = std::atan2(pointDist.x, pointDist.y) * Calculation::kRadToDeg;
    // �͈͂�0~360�ɂ����Ă�������
    if (distDeg < 0) distDeg += 360;
    // �l�p�`�̒��S����E��̒��_�Ɍ������x�N�g���̊p�x
    // ��������ɂق���3�������o��
    Vector2 rectVec = Vector2(otherRect.Right(), otherRect.Bottom()) - otherRect.GetPos();
    float rectDeg = std::atan2(rectVec.x, rectVec.y) * Calculation::kRadToDeg;
    if (distDeg > rectDeg && distDeg <= 180 - rectDeg) result.normal = Vector2::Down();
    if (distDeg > 180 - rectDeg && distDeg <= 180 + rectDeg) result.normal = Vector2::Left();
    if (distDeg > 180 + rectDeg && distDeg <= 360 - rectDeg) result.normal = Vector2::Up();
    if (distDeg > 360 - rectDeg || distDeg <= rectDeg) result.normal = Vector2::Right();

    return result;
}

CollisionStatus CircleCollider::CheckHitBox(BoxCollider& otherRect, Vector2 offset)
{
    return CollisionStatus();
}
