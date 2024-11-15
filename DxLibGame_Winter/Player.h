#pragma once
#include "Vector2.h"
#include <memory>
#include "GameObject.h"

// 物理クラスのプロトタイプ宣言
class Physics;
class CircleCollider;
class MapSystem;
class Camera;

/// <summary>
/// プレイヤーのクラスです。
/// </summary>
class Player : public GameObject
{
private:
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<CircleCollider> m_collider;
	std::shared_ptr<Camera> m_camera;

	using StateFunc_t = void(Player::*)();
	// 今のプレイヤーの状態
	StateFunc_t m_state;

	void Normal();
	void Attack();
	void Damage();
	void Death();
	void Move();
	void Dash();
public:
	/// <summary>
	/// 初期化
	/// </summary>
	Player(std::shared_ptr<Camera> camera);

	/// <summary>
	/// 入力をとって移動したり何したり
	/// </summary>
	void Update(const std::shared_ptr<MapSystem> map);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() const;

	/// <summary>
	/// 自分のPhysicsのvelocityを返す
	/// いまいちクラス間のデータの受け渡しがわからない
	/// </summary>
	/// <returns>自分の物理クラスの速度</returns>
	Vector2 GetVel() const;

	/// <summary>
	/// コライダー返すだけ
	/// </summary>
	/// <returns>コライダーのポインタ</returns>
	std::shared_ptr<CircleCollider> GetCollider() { return m_collider; }
};

