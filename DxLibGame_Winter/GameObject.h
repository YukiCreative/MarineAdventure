#pragma once
#include "Vector2.h"

/// <summary>
/// 座標を持つ
/// カメラの追尾に使ったり
/// 基底クラスでまとめてUpdateしたり
/// </summary>
class GameObject
{
protected:
	// 座標　中心座標で頼む
	Vector2 m_pos;
	bool m_isDeleted;
public:
	GameObject() : m_pos(), m_isDeleted(false) {}
	GameObject(Vector2 pos) : m_pos(pos), m_isDeleted(false) {}

	virtual void Update() = 0;
	virtual void Draw() const = 0;

	/// <summary>
	/// 座標を返す
	/// </summary>
	/// <returns>座標の参照</returns>
	Vector2 GetPos() const { return m_pos; }

	/// <summary>
	/// 消えたかどうか
	/// これを見てControllerが削除する
	/// </summary>
	bool IsDeleted() const { return m_isDeleted; }
};