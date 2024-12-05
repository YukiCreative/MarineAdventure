#pragma once
#include "Collider.h"

/// <summary>
/// 線分の当たり判定
/// </summary>
class LineCollider : public Collider
{
private:
	// posRefからの相対位置
	Vector2 m_firstPosOffset;
	Vector2 m_secondPosOffset;
public:
	LineCollider(Vector2& posRef, Vector2 firstPosOffset, const Vector2 secondPosOffset);

	Vector2 GetFirstPos() const { return m_pos + m_firstPosOffset; }
	Vector2 GetSecondPos() const { return m_pos + m_secondPosOffset; }
	// 中点返す
	Vector2 SegmentMidPoint()const { return (GetFirstPos() + GetSecondPos()) * 0.5f; };
protected:
	// 当たり判定のパターン増えていく問題
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;

	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& velocity) const override;
};

