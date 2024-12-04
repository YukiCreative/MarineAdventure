#include "CircleCollider.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include <algorithm>
#include <cmath>
#include "Calculation.h"
#include <DxLib.h>
#include "Geometry.h"
#include <vector>
#include <cassert>
#include <typeinfo>

namespace
{
    constexpr int kLineColNum = 4;
}

CircleCollider::CircleCollider(Vector2& pos, float radius) :
    Collider(ColKind::kCircle, pos),
    m_radius(radius)
{
}

CollisionStatus CircleCollider::CheckHitCircle(const CircleCollider& otherCircle) const 
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

CollisionStatus CircleCollider::CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const
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

CollisionStatus CircleCollider::CheckHitBox(const BoxCollider& otherRect) const
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

CollisionStatus CircleCollider::CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const
{
    // �����l�Ƃ̓����蔻��
    const CircleCollider& circle = *this;
    const BoxCollider& box = otherRect;

    // CollisionStatus�ƌ�_���܂Ƃ߂�
    using LineColStatus = std::pair<CollisionStatus, Vector2>;
    std::array<LineColStatus, kLineColNum> lineColStatus{};
    bool isHit = false;
    for (int i = 0; i < kLineColNum; ++i)
    {
        // �|�����[�t�B�Y����������
        lineColStatus[i].first = circle.CheckHitLine(*box.GetLineCol()[0], offset, lineColStatus[i].second);
        // ����͈�ł��������Ă�����OK
        isHit |= lineColStatus[i].first.isCollide;
    }

    CollisionStatus result;
    result.isCollide = isHit;
    // �������������ŁA��_���ł����݈ʒu�ɋ߂������̂߂荞�݂��̗p����
    // �ǂ��������Ă��Ȃ��Ƃ��́A�������������͈�����@�̂͂��Ȃ̂ł�����g��
    if (isHit)
    {
        LineColStatus nearestLine = lineColStatus[0];
        for (int i = 1; i < kLineColNum; ++i)
        {
            // ��NaV�̑傫����-1
            // �Ǝv�������K�p����ĂȂ�����
            // ���S�Ƀ_�E���L���X�g������
            if (nearestLine.second.SqrMagnitude() < lineColStatus[i].second.SqrMagnitude())
            {
                nearestLine = lineColStatus[i];
            }
        }
        result.overlap = nearestLine.first.overlap;
    }
    else
    {
        result.overlap = Vector2::Zero();
    }
    return result;
}

CollisionStatus CircleCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& velocity, Vector2& crossPos) const
{
    CollisionStatus result;
    // �����ċq�ϓI�Ɏ����𑀍삷�邱�ƂŁA���΂̓����蔻��ɗ��p���₷������
    const CircleCollider& circle = *this;
    const LineCollider& line = otherLine;

    // �~�̈ړ��ʃx�N�g���ƁA�ǐ���������邩�ǂ����𒲂ׂ�
    float segmentMinLength = Segment_Segment_MinLength(circle.GetPos(), velocity, line.GetFirstPos(), line.GetSecondPos());
    bool isCross = segmentMinLength == 0.0f;

    Vector2 futurePos = circle.GetPos() + velocity;
    // �~�̖����̈ʒu�Ɛ����̍ŋߖT�_���o��
    Vector2 futureNearestPos = geo::GetIntercept(circle.GetPos(), line.GetFirstPos(), line.GetSecondPos());

    // ���S���A�ړ��ʂ���AfutureNearestPos + ���a���߂�����
    Vector2 overlapTemp = futureNearestPos - futurePos;
    // �~�̔��a�̒����́A���S���ŋߖT�_�̌����̃x�N�g�����쐬
    Vector2 radiusVec = overlapTemp.GetNormalize() * circle.GetRadius();
    overlapTemp += radiusVec;

    // ������Ă����
    if (isCross)
    {
        result.overlap = overlapTemp;
        // ��_��Ԃ��Ă�����
        crossPos = futureNearestPos;
    }
    else
    {
        // ����
        result.overlap = -overlapTemp;
        // �����Ȃ�����
        crossPos = NaV();
    }

    // �������Ă��邩�́A���a���l�����ďo��
    result.isCollide = segmentMinLength <= circle.GetRadius();
    return result;
}
