#pragma once
#include "Collider.h"

/// <summary>
/// �~�`�̓����蔻��N���X
/// </summary>
class CircleCollider : public Collider
{
protected:
	/// <summary>
	/// ���a
	/// </summary>
	float m_radius;
public:
	CircleCollider(Vector2 pos, float radius);

	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="other">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(CircleCollider& other) override;
	/// <summary>
	/// �����蔻��̎擾(�΋�`)
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(BoxCollider& other) override;

	float GetRadius() { return m_radius; }
};

