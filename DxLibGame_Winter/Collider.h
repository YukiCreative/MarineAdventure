#pragma once
#include "Vector2.h"

class CircleCollider;
class BoxCollider;

/// <summary>
/// 当たり判定をつかさどる基底クラス
/// コライダーの相対座標も持っておく
/// </summary>
class Collider
{
protected:
	/// <summary>
	/// コライダーの相対座標
	/// Drawする座標からずらす感じで使う
	/// </summary>
	Vector2 m_posOffset;

public:

	/// <summary>
	/// 当たり判定の取得(対円形)
	/// </summary>
	/// <param name="other">円形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual bool CheckHit(CircleCollider other) = 0;
	/// <summary>
	/// 当たり判定の取得(対矩形)
	/// </summary>
	/// <param name="other">矩形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual bool CheckHit(BoxCollider other) = 0;
};

