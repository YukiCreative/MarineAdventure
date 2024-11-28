#pragma once
#include "Collider.h"

/// <summary>
/// 線分の当たり判定
/// </summary>
class LineCollider : public Collider
{
private:
	// これと、Colliderのm_posの二点で線分を表現
	Vector2 m_secondPos;
public:
	LineCollider(Vector2& firstPos, const Vector2& secondPos) :
		Collider(ColKind::kLine, firstPos),
		m_secondPos(secondPos)
	{
	}

	// 実はm_posを返している
	Vector2 GetFirstPos() const { return m_pos; }
	Vector2 GetSecondPos() const { return m_secondPos; }
protected:
	// 当たり判定のパターン増えていく問題
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;

	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& velocity) const override;
};

