#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
protected:
	/// <summary>
	/// 矩形の横の大きさ
	/// </summary>
	float m_rectHorizontalLength;
	/// <summary>
	/// 矩形の縦の長さ
	/// </summary>
	float m_rectVerticalLength;

public:
	BoxCollider(Vector2& pos, float h, float v);

	/// <summary>
	/// 当たり判定の取得(対円形)
	/// </summary>
	/// <param name="other">円形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual bool CheckHit(CircleCollider& other);
	/// <summary>
	/// 矩形と矩形の当たり判定
	/// </summary>
	/// <param name="other">矩形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual bool CheckHit(BoxCollider& other);

	// それぞれ端の座標を返す
	float Right();
	float Left();
	float Top();
	float Bottom();
};

