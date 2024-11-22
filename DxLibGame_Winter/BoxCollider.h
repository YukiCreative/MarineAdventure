#pragma once
#include "Collider.h"
#include <memory>

class CircleCollider;

class BoxCollider : public Collider
{
protected:
	/// <summary>
	/// 矩形の横の大きさ
	/// </summary>
	float m_rectWidth;
	/// <summary>
	/// 矩形の縦の長さ
	/// </summary>
	float m_rectHeight;

public:
	BoxCollider(Vector2& pos, float w, float h);

	// それぞれ端の座標を返す
	float Right() const;
	float Left() const;
	float Top() const;
	float Bottom() const;
protected:
	/// <summary>
	/// 当たり判定の取得(対円形)
	/// </summary>
	/// <param name="other">円形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	CollisionStatus CheckHitCircle(CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(CircleCollider& otherCircle, Vector2 offset) const override;
	/// <summary>
	/// 矩形と矩形の当たり判定
	/// </summary>
	/// <param name="other">矩形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	CollisionStatus CheckHitBox(BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(BoxCollider& otherRect, Vector2 offset) const override;
};

