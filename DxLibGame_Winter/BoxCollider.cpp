#include "BoxCollider.h"
#include "CircleCollider.h"
#include <algorithm>
#include <memory>
#include "Calculation.h"
#include "LineCollider.h"
#include <cassert>
#include <vector>

namespace
{
    constexpr int kLineColInBox = 4;
}

BoxCollider::BoxCollider(Vector2& pos, const float& w, const float& h) :
	Collider(ColKind::kBox, pos),
	m_rectWidth(w),
	m_rectHeight(h)
{
    // ���S����̑��΋������o���Ă܂�
    Vector2 topLeft =  Vector2(Left(), Top()) - GetPos();
    Vector2 bottomLeft =  Vector2(Left(), Bottom()) - GetPos();
    Vector2 topRight = Vector2(Right(), Top()) - GetPos();
    Vector2 bottomRight = Vector2(Right(), Bottom()) - GetPos();
    // �e�ӂ�Collider��
    //constexpr int offset = 10;
    //m_lines[static_cast<int>(LineDir::Top)] = std::make_shared<LineCollider>(m_pos, topLeft + Vector2(offset, 0), topRight + Vector2(-offset, 0)); // ��
    //m_lines[static_cast<int>(LineDir::Left)] = std::make_shared<LineCollider>(m_pos, topLeft + Vector2(0, offset), bottomLeft + Vector2(0, -offset)); // ��
    //m_lines[static_cast<int>(LineDir::Right)] = std::make_shared<LineCollider>(m_pos, bottomRight + Vector2(0, -offset), topRight + Vector2(0, offset)); // �E
    //m_lines[static_cast<int>(LineDir::Bottom)] = std::make_shared<LineCollider>(m_pos, bottomLeft + Vector2(offset, 0), bottomRight + Vector2(-offset, 0)); // ��
    // ���ꂼ��̐������n�_�ˏI�_�ˎn�_�łȂ���悤�ɍ��
    m_lines[static_cast<int>(LineDir::Top)]    = std::make_shared<LineCollider>(m_pos, topLeft,     topRight   ); // ��
    m_lines[static_cast<int>(LineDir::Right)]  = std::make_shared<LineCollider>(m_pos, topRight,    bottomRight); // �E
    m_lines[static_cast<int>(LineDir::Bottom)] = std::make_shared<LineCollider>(m_pos, bottomRight, bottomLeft ); // ��
    m_lines[static_cast<int>(LineDir::Left)]   = std::make_shared<LineCollider>(m_pos, bottomLeft,  topLeft    ); // ��
    
    for (auto& isValid : m_validLineCol)
    {
        isValid = true;
    }
}

// offset�t����ȊO�ς��Ȃ�����
BoxCollider::BoxCollider(Vector2& pos, const float& w, const float& h, const Vector2& offset) :
    Collider(ColKind::kBox, pos, offset),
    m_rectWidth(w),
    m_rectHeight(h)
{
    Vector2 topLeft = Vector2(Left(), Top()) - GetPos();
    Vector2 bottomLeft = Vector2(Left(), Bottom()) - GetPos();
    Vector2 topRight = Vector2(Right(), Top()) - GetPos();
    Vector2 bottomRight = Vector2(Right(), Bottom()) - GetPos();
    // m_pos�������Ă��܂�������ł�
    // ���ꂼ��̐������n�_�ˏI�_�ˎn�_�łȂ���悤�ɍ��
    m_lines[static_cast<int>(LineDir::Top)]    = std::make_shared<LineCollider>(m_pos, topLeft,     topRight,    offset); // ��
    m_lines[static_cast<int>(LineDir::Right)]  = std::make_shared<LineCollider>(m_pos, topRight,    bottomRight, offset); // �E
    m_lines[static_cast<int>(LineDir::Left)]   = std::make_shared<LineCollider>(m_pos, bottomLeft,  topLeft,     offset); // ��
    m_lines[static_cast<int>(LineDir::Bottom)] = std::make_shared<LineCollider>(m_pos, bottomRight, bottomLeft,  offset); // ��

    for (auto& isValid : m_validLineCol)
    {
        isValid = true;
    }
}

void BoxCollider::DrawColliderRange_Debug(const Vector2& cameraOffset) const
{
    // �l�p�̓����蔻�������
    //DrawBox(static_cast<int>(Left() - cameraOffset.x), static_cast<int>(Top() - cameraOffset.y), static_cast<int>(Right() - cameraOffset.x), static_cast<int>(Bottom() - cameraOffset.y), 0xff0000, false);

    // ��
    // ������͓������ʂ�`�悷�邱�Ƃ��m�F�ł��Ă���
    // ��
    
     //�����̕`����l����
    for (const auto& line : m_lines)
    {
        line->DrawColliderRange_Debug(cameraOffset);
    }
}

CollisionStatus BoxCollider::CheckHitCircle(const CircleCollider& otherCircle) const
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

    CollisionStatus result;
    result.isCollide = sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
    result.overlap = radiusVec - distVec;

    return result;
}

CollisionStatus BoxCollider::CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const
{
    //// �߂�ǂ���������~�̕��������Ă���Ă��Ƃł����H
    //Vector2 circlePos = otherCircle.GetPos() - offset;
    //// ��`�̕ӂŁA�~�̒��S���W�ƈ�ԋ߂��_���o��
    //Vector2 nearestPoint;
    //nearestPoint.x = std::clamp(circlePos.x, Left(), Right());
    //nearestPoint.y = std::clamp(circlePos.y, Top(), Bottom());

    //// �o������_�̋������A�~�̔��a�ȉ��Ȃ瓖�����Ă���
    //Vector2 distVec = circlePos - nearestPoint;
    //float sqrDist = distVec.SqrMagnitude();
    //// �~�̔��a�̑傫���������AdistVec�̌����̃x�N�g������肽��
    //Vector2 radiusVec = distVec.GetNormalize() * otherCircle.GetRadius();

    //CollisionStatus result;
    //result.isCollide = sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
    //result.overlap = radiusVec - distVec;

    //return result;

    const CircleCollider& circle = otherCircle;
    const BoxCollider& box = *this;

    CollisionStatus result;
    Vector2 nearestCrossPos;
    bool isCross = false;
    std::vector<float> lineDist;
    std::vector<CollisionStatus> lineColStatus;
    // ���ݗL���ȃ��C���R���C�_�[�Ƃ̐ڐG����
    for (int i = 0; i < kLineColInBox; ++i)
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