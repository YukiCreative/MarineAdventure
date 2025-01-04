#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include <memory>
#include <string>
#include <list>

// プロトタイプ宣言
class Physics;
class CircleCollider;
class Camera;
class Input;
class MapSystem;
class Animation;

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
	// コンポーネント
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<CircleCollider> m_collider;
	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_idleAnim;

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
	// 接触したマップチップの面の角度
	std::list<int> m_contactAngles;
	Vector2 m_velocity;

	void GameOver();

	// 状態関数
	// 一段格上げしてクラスにしてもいいかも？
	void Normal(Input& input, Vector2& axis);
	void Move(Input& input, Vector2& axis);
	void Dash(Input& input, Vector2& axis);
	void Attack(Input& input, Vector2& axis);
	void StrongAttack(Input& input, Vector2& axis);
	void Damage(Input& input, Vector2& axis);
	void Death(Input& input, Vector2& axis);
	// 敵にダメージを与えた後の硬直
	void Attacked(Input& input, Vector2& axis);
	// 地上ステート
	void GNormal(Input& input, Vector2& axis);
	void GMove(Input& input, Vector2& axis);
	void GDash(Input& input, Vector2& axis);
	void Jump(Input& input, Vector2& axis);

	void SetStateNormal();
	bool CheckEnvironmentChanged();
	void CollideToMapChips();
public:
	/// <summary>
	/// 初期化
	/// </summary>
	Player(Camera& camera, Vector2 spawnPos);
	~Player();

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
	// ダメージを与えたいときに流してもらう
	void OnDamage(int damage = 1);
	// physicsのオーバーラップ
	void AddForce(const Vector2& force);
	void Stop();
	// 攻撃時の振る舞い
	void OnAttack();

	Vector2 GetVel() const { return m_velocity; }
};