#pragma once
#include "Vector2.h"
#include <memory>

class CircleCollider;
class BoxCollider;
class LineCollider;

enum class ColKind
{
	kCircle,
	kBox,
	kLine,
};

/// <summary>
/// コライダーが計算した後に出てくるいろんな情報をひとまとめにして返したかった
/// </summary>
struct CollisionStatus
{
	// 当たっているか
	bool isCollide = false;
	// 当たった面に垂直に、どれくらいの向き、大きさでめり込んでいるかを出してくれます
	Vector2 overlap = Vector2::Zero();
};

/// <summary>
/// 当たり判定をつかさどる基底クラス
/// </summary>
class Collider
{
protected:
	/// <summary>
	/// 自分がアタッチされているオブジェクトの座標を参照
	/// </summary>
	Vector2& m_pos;

	// m_posからどれだけずらすか
	Vector2 m_offset;

	const ColKind m_kind;

public:
	Collider(const ColKind& kind, Vector2& pos);
	Collider(const ColKind& kind, Vector2& pos, const Vector2& offset);

	// ゲームオブジェクトの位置ではないので注意
	Vector2 GetPos() const { return m_pos + m_offset; }
	// 使うなよ
	Vector2* GetPVec() const { return &m_pos; }
	ColKind GetKind() const { return m_kind; }

	CollisionStatus CheckHit(Collider& other) const;
	// 補正あり これから加算する移動量を加味するときなどに有効
	CollisionStatus CheckHit(Collider& other, const Vector2& offset) const;

	// 自分の衝突範囲を可視化
	virtual void DrawColliderRange_Debug(const Vector2& cameraOffset) const = 0;

protected:

	/// <summary>
	/// 当たり判定の取得(対円形)
	/// </summary>
	/// <param name="other">円形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual CollisionStatus CheckHitCircle(const CircleCollider& other) const = 0;
	virtual CollisionStatus CheckHitCircle(const CircleCollider& other, const Vector2& offset) const = 0;
	/// <summary>
	/// 当たり判定の取得(対矩形)
	/// </summary>
	/// <param name="other">矩形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual CollisionStatus CheckHitBox(const BoxCollider& other) const = 0;
	virtual CollisionStatus CheckHitBox(const BoxCollider& other, const Vector2& offset) const = 0;

	virtual CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& offset) const = 0;
};

