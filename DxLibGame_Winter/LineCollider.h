#pragma once
#include "Collider.h"

/// <summary>
/// 線分の当たり判定
/// </summary>
class LineCollider : public Collider
{
private:
	// これと、Colliderのm_posの二点で線分を表現
	Vector2 m_firstPos;
	Vector2 m_secondPos;
public:
	// 基本の座標を参照して、それに合わせて線分の始点と終点を求める
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
	// 当たり判定のパターン増えていく問題
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;

	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& velocity, Vector2& crossPos) const override;
};

