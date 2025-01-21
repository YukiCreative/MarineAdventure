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
	// こいつが出現した元のマップ座標
	Vector2Int m_mapPos;
	bool m_isDeleted;
public:
	GameObject() : m_pos(), m_isDeleted(false), m_mapPos() {}
	GameObject(const Vector2& pos) : m_pos(pos), m_isDeleted(false), m_mapPos() {}
	GameObject(const Vector2& pos, const Vector2Int& mapPos) : m_pos(pos), m_isDeleted(false), m_mapPos(mapPos) {}

	virtual void Update() = 0;
	virtual void Draw() const = 0;

	/// <summary>
	/// 座標を返す
	/// </summary>
	/// <returns>座標の参照</returns>
	Vector2 GetPos() const { return m_pos; }
	Vector2Int GetBaseMapPos() const { return m_mapPos; }

	/// <summary>
	/// 消えたかどうか
	/// これを見てControllerが削除する
	/// </summary>
	bool IsDeleted() const { return m_isDeleted; }
};