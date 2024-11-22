#pragma once
#include "Vector2.h"
#include <memory>
#include "CollisionStatus.h"

class CircleCollider;
class BoxCollider;

enum class ColKind
{
	kCircle,
	kBox,
};

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

	const ColKind m_kind;

public:
	Collider(ColKind kind, Vector2& pos);

	void SetOffset(Vector2 value) { m_posOffset = value; }
	Vector2 GetPos() { return m_pos; }
	// 使うなよ
	Vector2* GetPVec() { return &m_pos; }
	ColKind GetKind() { return m_kind; }

	CollisionStatus CheckHit(Collider& other);
	// 補正あり これから加算する移動量を加味するときなどに有効
	CollisionStatus CheckHit(Collider& other, const Vector2& offset);

protected:
	// ここから先の関数は外部には見せない
	// 外部からはCheckHit(Collider)呼んでもらって、その中でフラグ使って分岐する
	// でもこれやると当たり判定の種類が増えるごとにどんどん組み合わせが増えて関数名が増えていくじゃない
	// でもよく考えたらオーバーロードが増えるのは同じでした

	/// <summary>
	/// 当たり判定の取得(対円形)
	/// </summary>
	/// <param name="other">円形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual CollisionStatus CheckHitCircle(CircleCollider& other) = 0;
	virtual CollisionStatus CheckHitCircle(CircleCollider& other, Vector2 offset) = 0;
	/// <summary>
	/// 当たり判定の取得(対矩形)
	/// </summary>
	/// <param name="other">矩形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual CollisionStatus CheckHitBox(BoxCollider& other) = 0;
	virtual CollisionStatus CheckHitBox(BoxCollider& other, Vector2 offset) = 0;
};

