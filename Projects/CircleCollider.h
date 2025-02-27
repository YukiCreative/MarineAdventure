#pragma once
#include "Collider.h"
#include <memory>

class BoxCollider;
class LineCollider;

/// <summary>
/// 円形の当たり判定クラス
/// </summary>
class CircleCollider : public Collider
{
protected:
	/// <summary>
	/// 半径
	/// </summary>
	float m_radius;
	
public:
	CircleCollider(Vector2& pos, const float& radius);
	CircleCollider(Vector2& pos, const float& radius, const Vector2& offset);

	float GetRadius() const { return m_radius; }

	void DrawColliderRange_Debug(const Vector2& cameraOffset) const override;

protected:
	/// <summary>
	/// 当たり判定の取得(対円形)
	/// </summary>
	/// <param name="otherCircle">円形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;
	/// <summary>
	/// 当たり判定の取得(対矩形)
	/// 線分四つの当たり判定
	/// </summary>
	/// <param name="otherRect">矩形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& velocity) const override;
};

