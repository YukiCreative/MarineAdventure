#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
protected:
	/// <summary>
	/// ��`�̉��̑傫��
	/// </summary>
	float m_rectHorizontalLength;
	/// <summary>
	/// ��`�̏c�̒���
	/// </summary>
	float m_rectVerticalLength;

public:
	BoxCollider(Vector2& pos, float h, float v);

	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="other">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(CircleCollider& other);
	/// <summary>
	/// ��`�Ƌ�`�̓����蔻��
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(BoxCollider& other);

	// ���ꂼ��[�̍��W��Ԃ�
	float Right();
	float Left();
	float Top();
	float Bottom();
};

