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
    result.normal = -distUnit;

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
    result.normal = -distUnit;

    return result;
}

CollisionStatus CircleCollider::CheckHitBox(BoxCollider& otherRect) const
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
    float distDeg = std::atan2(pointDist.y, pointDist.x) * Calculation::kRadToDeg;
    // �͈͂�0~360�ɂ����Ă�������
    if (distDeg < 0) distDeg += 360;
    // �l�p�`�̒��S����E��̒��_�Ɍ������x�N�g���̊p�x
    // ��������ɂق���3�������o��
    Vector2 rectVec = Vector2(otherRect.Right(), otherRect.Bottom()) - otherRect.GetPos();
    float rectDeg = std::atan2(rectVec.y, rectVec.x) * Calculation::kRadToDeg;
    if (distDeg > rectDeg && distDeg <= 180 - rectDeg) result.normal = Vector2::Down();
    if (distDeg > 180 - rectDeg && distDeg <= 180 + rectDeg) result.normal = Vector2::Left();
    if (distDeg > 180 + rectDeg && distDeg <= 360 - rectDeg) result.normal = Vector2::Up();
    if (distDeg > 360 - rectDeg || distDeg <= rectDeg) result.normal = Vector2::Right();

    return result;
}

CollisionStatus CircleCollider::CheckHitBox(BoxCollider& otherRect, const Vector2& offset) const
{
    // �␳
    Vector2 correctedPos = m_pos + offset;
    // ��`�̕ӂŁA�~�̒��S���W�ƈ�ԋ߂��_���o��
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(correctedPos.x, otherRect.Left(), otherRect.Right());
    nearestPoint.y = std::clamp(correctedPos.y, otherRect.Top(), otherRect.Bottom());

    // �o������_�̋������A�~�̔��a�ȉ��Ȃ瓖�����Ă���
    Vector2 distVec = correctedPos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // �~�̔��a�̑傫���������AdistVec�̌����̃x�N�g������肽��
    Vector2 radiusVec = distVec.GetNormalize() * m_radius;

    CollisionStatus result;
    result.isCollide = sqrDist <= m_radius * m_radius;
    result.overlap = radiusVec - distVec;
    // ������̒��S���m���Ȃ����x�N�g�����ǂ�Ȍ������Ŕ���
    // ����㉺�t�ɂȂ���
    Vector2 pointDist = correctedPos - otherRect.GetPos();
    float distDeg = std::atan2(pointDist.x, pointDist.y) * Calculation::kRadToDeg;
    // �͈͂�0~360�ɂ����Ă�������
    if (distDeg < 0) distDeg += 360;
    // �l�p�`�̒��S����E��̒��_�Ɍ������x�N�g���̊p�x
    // ��������ɂق���3�������o��
    Vector2 rectVec = Vector2(otherRect.Right(), otherRect.Bottom()) - otherRect.GetPos();
    float rectDeg = std::atan2(5, 1) * Calculation::kRadToDeg;
    printf("rectVec: x=%f,Y=%f\n", rectVec.x, rectVec.y);
    printf("distDeg=%f\n", distDeg);
    printf("rectDeg=%f\n", rectDeg);
    if (distDeg > rectDeg && distDeg <= 180 - rectDeg) result.normal = Vector2::Down();
    if (distDeg > 180 - rectDeg && distDeg <= 180 + rectDeg) result.normal = Vector2::Left();
    if (distDeg > 180 + rectDeg && distDeg <= 360 - rectDeg) result.normal = Vector2::Up();
    if (distDeg > 360 - rectDeg || distDeg <= rectDeg) result.normal = Vector2::Right();

    return result;
}
