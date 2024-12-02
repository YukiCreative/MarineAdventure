#pragma once
#include "Collider.h"
#include <memory>
#include <array>

class CircleCollider;
class LineCollider;

class BoxCollider : public Collider
{
private:
	/// <summary>
	/// 矩形の横の大きさ
	/// </summary>
	float m_rectWidth;
	/// <summary>
	/// 矩形の縦の長さ
	/// </summary>
	float m_rectHeight;

	// LineColliderを持ってみる
	// 円と矩形の当たり判定に使用する
	// 矩形と矩形はそのまま自分の幅と高さで判定する
	using LineArray_t = std::array<std::shared_ptr<LineCollider>, 4>;
	LineArray_t m_lines;

public:
	BoxCollider(Vector2& pos, float w, float h);

	// それぞれ端の座標を返す
	float Right() const { return m_pos.x + m_rectWidth * 0.5f; };
	float Left() const { return m_pos.x - m_rectWidth * 0.5f; };
	float Top() const { return m_pos.y - m_rectHeight * 0.5f; };
	float Bottom() const { return m_pos.y + m_rectHeight * 0.5f; };

	const LineArray_t& GetLineCol() const { return m_lines; };
protected:
	/// <summary>
	/// 当たり判定の取得(対円形)
	/// </summary>
	/// <param name="other">円形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;
	/// <summary>
	/// 矩形と矩形の当たり判定
	/// </summary>
	/// <param name="other">矩形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	virtual CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& offset, Vector2& crossPos) const override;
};

