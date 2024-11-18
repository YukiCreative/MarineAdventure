#pragma once
#include "Vector2.h"

/// <summary>
/// 座標を持つ
/// カメラの追尾に使う
/// </summary>
class GameObject
{
protected:
	// 座標　中心座標で頼む
	Vector2 m_pos;
public:

	/// <summary>
	/// 座標を返す
	/// </summary>
	/// <returns>座標の参照</returns>
	Vector2 GetPos() { return m_pos; }
};