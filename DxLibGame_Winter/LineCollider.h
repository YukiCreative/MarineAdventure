#pragma once
#include "Collider.h"

/// <summary>
/// �����̓����蔻��
/// </summary>
class LineCollider : public Collider
{
private:
	// posRef����̑��Έʒu
	Vector2 m_firstPosOffset;
	Vector2 m_secondPosOffset;
public:
	LineCollider(Vector2& posRef, Vector2 firstPosOffset, const Vector2 secondPosOffset);

	Vector2 GetFirstPos() const { return m_pos + m_firstPosOffset; }
	Vector2 GetSecondPos() const { return m_pos + m_secondPosOffset; }
	// ���_�Ԃ�
	Vector2 SegmentMidPoint()const { return (GetFirstPos() + GetSecondPos()) * 0.5f; };
protected:
	// �����蔻��̃p�^�[�������Ă������
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;

	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& velocity) const override;
};

