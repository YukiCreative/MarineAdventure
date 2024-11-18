#pragma once
#include "Vector2.h"
#include <memory>

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

	bool CheckHit(std::shared_ptr<Collider> other);
	// Vector2の参照を渡してくれれば重なっている部分の向きと長さを返します
	bool CheckHit(std::shared_ptr<Collider> other, Vector2& overlapLength);

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
	virtual bool CheckHitCircle(std::shared_ptr<CircleCollider> other);
	/// <summary>
	/// 当たり判定の取得(対矩形)
	/// </summary>
	/// <param name="other">矩形の当たり判定</param>
	/// <returns>接触しているかどうか</returns>
	virtual bool CheckHitBox(std::shared_ptr<BoxCollider> other);
};

