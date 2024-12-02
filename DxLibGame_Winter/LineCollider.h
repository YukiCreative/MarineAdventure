#pragma once
#include "Collider.h"

/// <summary>
/// �����̓����蔻��
/// </summary>
class LineCollider : public Collider
{
private:
	// ����ƁACollider��m_pos�̓�_�Ő�����\��
	Vector2 m_firstPos;
	Vector2 m_secondPos;
public:
	// ��{�̍��W���Q�Ƃ��āA����ɍ��킹�Đ����̎n�_�ƏI�_�����߂�
	LineCollider(Vector2& pivot, Vector2 firstPosOffset, Vector2 secondPosOffset) :
		Collider(ColKind::kLine, pivot),
		m_firstPos(firstPosOffset),
		m_secondPos(secondPosOffset)
	{
	}

	// 
	Vector2 GetFirstPos() const { return m_firstPos - m_pos; }
	Vector2 GetSecondPos() const { return m_secondPos ; }
protected:
	// �����蔻��̃p�^�[�������Ă������
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;

	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& velocity, Vector2& crossPos) const override;
};

