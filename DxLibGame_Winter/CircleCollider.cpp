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
    const CircleCollider& circle = *this;
    const BoxCollider& box = otherRect;

    CollisionStatus result;
    Vector2 nearestCrossPos;
    bool isCross = false;
    std::vector<float> lineDist;
    std::vector<CollisionStatus> lineColStatus;
    // ���ݗL���ȃ��C���R���C�_�[�Ƃ̐ڐG����
    for (int i = 0; i < kLineColNum; ++i)
    {
        if (!box.GetIsLineValid(static_cast<LineDir>(i))) continue;
        // �|�����[�t�B�Y����
        lineColStatus.push_back(circle.CheckHit(*box.GetLineCol()[i], offset));
        result.isCollide |= lineColStatus.back().isCollide; // ���ǉ��������
        // �����ŁAoverlap���擾���邽�߂ɁA���ݒn�_�����ԋ߂��������o������
        // ���ݒn�_����A���ꂼ��̐����̒��S�֌������x�N�g���̑傫�����ׂ�
        lineDist.push_back((circle.GetPos() - box.GetLineCol()[i]->SegmentMidPoint()).SqrMagnitude());
    }
    // ��ԋ߂�����overlap���̗p
    auto it = std::min_element(lineDist.begin(), lineDist.end());
    size_t index = std::distance(lineDist.begin(), it);
    if (lineColStatus.size() == 0)
    {
        result.overlap = Vector2::Zero();
    }
    else
    {
        result.overlap = lineColStatus[index].overlap;
    }
    return result;
}

CollisionStatus CircleCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& velocity) const
{
    CollisionStatus result;
    // �����ċq�ϓI�Ɏ����𑀍삷�邱�ƂŁA���΂̓����蔻��ɗ��p���₷������
    const CircleCollider& circle = *this;
    const LineCollider& line = otherLine;
    Vector2 futurePos = circle.GetPos() + velocity;

    // �~�̈ړ��ʃx�N�g���ƁA�ǐ���������邩�ǂ����𒲂ׂ�
    float segmentMinLength = Segment_Segment_MinLength(circle.GetPos(), futurePos, line.GetFirstPos(), line.GetSecondPos());
    bool isCross = (segmentMinLength == 0.0f);

    // �������Ă��邩�́A���a���l�����ďo��
    result.isCollide = (segmentMinLength < circle.GetRadius());

    // �~�̖����̈ʒu�Ɓu�����v�̍ŋߖT�_���o��
    Vector2 futureNearestPos = geo::GetSegmentIntercept(futurePos, line.GetFirstPos(), line.GetSecondPos());
    // �������ꂪ�����̒[�Ȃ�߂荞�܂Ȃ��������Ƃ�
    if (futureNearestPos == line.GetFirstPos() || futureNearestPos == line.GetSecondPos())
    {
        result.overlap = Vector2::Zero();
        return result;
    }

    // ������Ă����
    if (isCross)
    {
        // ���S���A�ړ��ʂ���AfutureNearestPos + ���a���߂�����
        Vector2 closestToNext = futurePos - futureNearestPos;
        // �~�̔��a�̒����́A���S���ŋߖT�_�̌����̃x�N�g�����쐬
        Vector2 closestToNextN = closestToNext.GetNormalize();
        Vector2 radiusVec = closestToNextN * circle.GetRadius();
        Vector2 overlap = radiusVec + closestToNext;
        result.overlap = overlap;
    }
    else
    {
        // ���̏ꍇ���S���A�ړ��ʂ��甼�a - futureNearestPos�����߂�����
        Vector2 nextToClosest = futureNearestPos - futurePos;
        // �~�̔��a�̒����́A���S���ŋߖT�_�̌����̃x�N�g�����쐬
        Vector2 nextToClosestN = nextToClosest.GetNormalize();
        Vector2 radiusVec = nextToClosestN * circle.GetRadius();
        Vector2 overlap = radiusVec - nextToClosest;
        result.overlap = overlap;
    }

    return result;
}
