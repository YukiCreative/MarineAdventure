#pragma once
#include "Collider.h"
#include <memory>

class CircleCollider;

class BoxCollider : public Collider
{
protected:
	/// <summary>
	/// ��`�̉��̑傫��
	/// </summary>
	float m_rectWidth;
	/// <summary>
	/// ��`�̏c�̒���
	/// </summary>
	float m_rectHeight;

public:
	BoxCollider(Vector2& pos, float w, float h);

	// ���ꂼ��[�̍��W��Ԃ�
	float Right();
	float Left();
	float Top();
	float Bottom();
protected:
	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="other">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	CollisionStatus CheckHitCircle(CircleCollider& otherCircle) override;
	CollisionStatus CheckHitCircle(CircleCollider& otherCircle, Vector2 offset) override;
	/// <summary>
	/// ��`�Ƌ�`�̓����蔻��
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	CollisionStatus CheckHitBox(BoxCollider& otherRect) override;
	CollisionStatus CheckHitBox(BoxCollider& otherRect, Vector2 offset) override;
};

