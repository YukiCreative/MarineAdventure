#pragma once
#include "Vector2.h"
#include <memory>

// 物理クラスのプロトタイプ宣言
class Physics;
class CircleCollider;
class MapSystem;

/// <summary>
/// プレイヤーのクラスです。
/// </summary>
class Player
{
private:
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<CircleCollider> m_collider;
	// ざっひょう
	Vector2 m_pos;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	Player();

	/// <summary>
	/// 入力をとって移動したり何したり
	/// </summary>
	void Update(const std::shared_ptr<MapSystem> map);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 自分のPhysicsのvelocityを返す
	/// いまいちクラス間のデータの受け渡しがわからない
	/// </summary>
	/// <returns></returns>
	Vector2 GetVel();

	/// <summary>
	/// コライダー返すだけ
	/// </summary>
	/// <returns>コライダーのポインタ</returns>
	std::shared_ptr<CircleCollider> Collider() { return m_collider; }
};

