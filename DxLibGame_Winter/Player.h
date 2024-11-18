#pragma once
#include "Vector2.h"
#include <memory>
#include "GameObject.h"
#include <string>

// プロトタイプ宣言
class Physics;
class CircleCollider;
class MapSystem;
class Camera;
class Input;

/// <summary>
/// プレイヤーのクラスです。
/// </summary>
class Player : public GameObject
{
private:
	std::unique_ptr<Physics> m_physics;
	std::unique_ptr<CircleCollider> m_collider;
	Camera& m_camera;

	using StateFunc_t = void(Player::*)(Input& input, Vector2& axis);
	// 今のプレイヤーの状態
	StateFunc_t m_state;
	// 仮で今の状態を可視化
	std::string m_graphic;
	// 現在の状態が何フレーム持続しているか　とかに使います
	int m_stateFrameCount;
	// 体力
	int m_hp;

	void Normal(Input& input, Vector2& axis);
	void Move(Input& input, Vector2& axis);
	void Dash(Input& input, Vector2& axis);
	void Attack(Input& input, Vector2& axis);
	void StrongAttack(Input& input, Vector2& axis);
	void Damage(Input& input, Vector2& axis);
	void Death(Input& input, Vector2& axis);

	void SetStateNormal();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	Player(Camera& camera);

	/// <summary>
	/// 入力をとって移動したり何したり
	/// </summary>
	void Update(MapSystem& map);
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
	CircleCollider& GetCollider();
};