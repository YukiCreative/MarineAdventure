#pragma once
#include "Collider.h"
#include <memory>

class BoxCollider;
class LineCollider;

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

	float GetRadius() const { return m_radius; }

protected:
	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="otherCircle">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;
	/// <summary>
	/// �����蔻��̎擾(�΋�`)
	/// </summary>
	/// <param name="otherRect">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& velocity) const override;
};

