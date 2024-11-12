#pragma once
#include "Vector2.h"

class CircleCollider;
class BoxCollider;

/// <summary>
/// 当たり判定をつかさどる基底クラス
/// </summary>
class Collider
{
protected:
	/// <summary>
	/// コライダーの相対座標
	/// Drawする座標からずらす感じで使う
	/// </summary>
	Vector2 m_posOffset;

	/// <summary>
	/// 自分がアタッチされているオブジェクトの座標を参照
	/// </summary>
	Vector2& m_pos;
public:
	Collider(Vector2& pos);

	/// <summary>
	/// 当たり判定の取得(対円形)
	/// </summary>
	/// <param name="other">円形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual bool CheckHit(CircleCollider& other) = 0;
	/// <summary>
	/// 当たり判定の取得(対矩形)
	/// </summary>
	/// <param name="other">矩形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual bool CheckHit(BoxCollider& other) = 0;

	void SetOffset(Vector2 value) { m_posOffset = value; }
	Vector2 GetPos() { return m_pos; }
};

