#pragma once
#include "Collider.h"
#include <memory>

class BoxCollider;

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
	CircleCollider(Vector2& pos, float radius);

	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="otherCircle">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(std::shared_ptr<CircleCollider> otherCircle) override;
	/// <summary>
	/// �����蔻��̎擾(�΋�`)
	/// </summary>
	/// <param name="otherRect">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(std::shared_ptr<BoxCollider> otherRect) override;

	float GetRadius() { return m_radius; }
};

