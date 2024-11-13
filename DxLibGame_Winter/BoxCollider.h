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

	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="other">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(std::shared_ptr<CircleCollider> otherCircle);
	/// <summary>
	/// ��`�Ƌ�`�̓����蔻��
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(std::shared_ptr<BoxCollider> otherRect);

	// ���ꂼ��[�̍��W��Ԃ�
	float Right();
	float Left();
	float Top();
	float Bottom();
};

