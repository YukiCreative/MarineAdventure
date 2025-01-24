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
	LineCollider(Vector2& posRef, const Vector2& firstPosOffset, const Vector2& secondPosOffset);
	LineCollider(Vector2& posRef, const Vector2& firstPosOffset, const Vector2& secondPosOffset, const Vector2& offset);

	Vector2 GetFirstPos() const { return GetPos() + m_firstPosOffset; }
	Vector2 GetSecondPos() const { return GetPos() + m_secondPosOffset; }
	// 中点返す
	Vector2 SegmentMidPoint()const { return (GetFirstPos() + GetSecondPos()) * 0.5f; };

	void DrawColliderRange_Debug(const Vector2& cameraOffset) const override;

	// 線分の始点⇒終点の単位ベクトルを返す
	Vector2 UnitVector() const;
protected:
	// 当たり判定のパターン増えていく問題
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;

	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& velocity) const override;
};

