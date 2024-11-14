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
	/// 座標の参照を返す
	/// 見るだけにしてもらえると助かります
	/// </summary>
	/// <returns>座標の参照</returns>
	Vector2& GetPosRef() { return m_pos; }
};