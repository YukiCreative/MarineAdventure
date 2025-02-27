#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include <memory>
#include <string>
#include <list>
#include "HitPoint.h"

// プロトタイプ宣言
class Physics;
class CircleCollider;
class Camera;
class Input;
class MapSystem;
class Animation;
class HitPoints;
class ObjectsController;

enum class PlayerState
{
	kNormal,
	kMove,
	kDash,
	kAttack,
	kStrongAttack,
	kDamage,
	kDeath,
	kDisappear
};

/// <summary>
/// プレイヤーのクラスです。
/// </summary>
class Player : public GameObject
{
private:
	// コンポジション
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<CircleCollider> m_collider;

	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_idleAnim;
	std::shared_ptr<Animation> m_jumpAnim;
	std::shared_ptr<Animation> m_fallAnim;
	std::shared_ptr<Animation> m_damageAnim;
	std::shared_ptr<Animation> m_attackAnim;
	std::shared_ptr<Animation> m_walkAnim;
	std::shared_ptr<Animation> m_dashAnim;
	std::shared_ptr<Animation> m_deathAnim;

	std::weak_ptr<MapSystem> m_map;
	Camera& m_camera;
	std::weak_ptr<ObjectsController> m_objCont;
	HitPoints& m_hpUI;

	using StateFunc_t = void(Player::*)(Input& input, Vector2& axis);
	// 今のプレイヤーの状態
	StateFunc_t m_state;
	// 仮で今の状態を可視化
	std::string m_stateText;
	// 現在の状態が何フレーム持続しているか　とかに使います
	int m_stateFrameCount;
	// 体力
	HitPoint m_hp;
	// 今フレームの移動量が記録される
	Vector2 m_velocity;
	// このフレームに接触した当たり判定で、どれだけめり込んだかが記録される
	std::list<Vector2> m_overlaps;
	// 自分が左を向いているか
	bool m_isLeft;

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
	void DisAppear(Input& input, Vector2& axis);
	// 敵にダメージを与えた後の硬直
	void Attacked(Input& input, Vector2& axis);
	// 地上ステート
	void GNormal(Input& input, Vector2& axis);
	void GMove(Input& input, Vector2& axis);
	void GDash(Input& input, Vector2& axis);
	void Air(Input& input, Vector2& axis);

	void SetStateNormal();
	void SetStateAttack();
	void SetStateJump();
	bool CheckEnvironmentChanged();
	void CollideToMapChips();
	void ChangeState(StateFunc_t nextState);
	void ChangeAnimation(const std::shared_ptr<Animation>& setAnim);
	// 今の入力から、アニメーションの向きを変える
	void ChangeDirection(const Vector2& axis);
	// 落下していたら、落下アニメーションに変える関数
	void ChangeFallAnim();
	void PlayWalkSound();
	void ChangeRotation();
	bool CheckFallOffTheStage();
	void InstantDeath();
public:
	/// <summary>
	/// 初期化
	/// </summary>
	Player(Camera& camera, Vector2 spawnPos, HitPoints& hpUI);
	~Player();

	// コンストラクタでは取得しきれないものを取得
	void Init(std::weak_ptr<MapSystem> map, std::weak_ptr<ObjectsController> objCont);

	/// <summary>
	/// 入力をとって移動したり何したり
	/// </summary>
	void Update() override;
	void AnimationUpdate();
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
	void OnRecovery(const int recoverAmount = 1);

	Vector2 GetVel() const { return m_velocity; }
	// 指定した座標に瞬間移動
	void Teleportation(Vector2 worldPos) { m_pos = worldPos; }

	bool IsGround();
};