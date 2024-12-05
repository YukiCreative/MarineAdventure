#pragma once
#include "Vector2.h"
#include <memory>
#include "GameObject.h"
#include <string>

// プロトタイプ宣言
class Physics;
class CircleCollider;
class Camera;
class Input;
class MapSystem;

enum class PlayerState
{
	kNormal,
	kMove,
	kDash,
	kAttack,
	kStrongAttack,
	kDamage,
	kDeath
};

/// <summary>
/// プレイヤーのクラスです。
/// </summary>
class Player : public GameObject
{
private:
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<CircleCollider> m_collider;

	std::weak_ptr<MapSystem> m_map;
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
	int m_graphHandle;

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
	Player(Camera& camera, Vector2 spawnPos);

	// コンストラクタでは取得しきれないものを取得
	void Init(std::weak_ptr<MapSystem> map) { m_map = map; }

	/// <summary>
	/// 入力をとって移動したり何したり
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() const override;

	/// <summary>
	/// 自分のPhysicsのvelocityを返す
	/// </summary>
	/// <returns>自分の物理クラスの速度</returns>
	Vector2 GetVel() const;

	/// <summary>
	/// コライダー返すだけ
	/// </summary>
	/// <returns>コライダーの参照</returns>
	CircleCollider& GetCollider() const { return *m_collider; }

	/// <summary>
	/// 現在の状態を取る
	/// </summary>
	/// <param name="stateID"></param>
	/// <returns></returns>
	bool CheckState(PlayerState stateID) const;
};

