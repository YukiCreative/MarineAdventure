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
	float Right() const;
	float Left() const;
	float Top() const;
	float Bottom() const;
protected:
	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="other">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	bool CheckHitCircle(CircleCollider& otherCircle) const override;
	bool CheckHitCircle(CircleCollider& otherCircle, const Vector2& offset) const override;
	/// <summary>
	/// ��`�Ƌ�`�̓����蔻��
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	bool CheckHitBox(BoxCollider& otherRect) const override;
	bool CheckHitBox(BoxCollider& otherRect, const Vector2& offset) const override;
};

