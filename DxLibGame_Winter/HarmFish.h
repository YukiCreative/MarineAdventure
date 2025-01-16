#pragma once
#include "Enemy.h"
#include <memory>
#include <string>

class CircleCollider;
class Animation;

class HarmFish : public Enemy
{
private:
	int m_stateFrameCount;
	// 追尾状態に移行するかどうかを表す数値
	int m_chasePoint;
	std::shared_ptr<CircleCollider> m_collider;

	// アニメーション関連
	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_idleAnim;
	std::shared_ptr<Animation> m_chaseAnim;
	std::shared_ptr<Animation> m_damageAnim;
	std::shared_ptr<Animation> m_deathAnim;

	// ステート
	using StateFunc_t = void (HarmFish::*)();
	StateFunc_t m_state;
	void Idle();
	void Chase();
	void Attacked();
	void Damage();
	void Death();

	// プレイヤーとの距離を測って、状態遷移するための点数をつける
	// 離れていればマイナスに、近づけばプラスに
	int ScoreChasePoint();
	// スコアを矯正する
	// スコアをクラス化してそっちに実装するのが確かにいい
	// が、めんどくさい
	void ChasePointValidation();

	// 当たり判定をまとめた
	void HitToPlayer();
	void HitToMap();

	void ChangeDirection();
	void ChangeState(StateFunc_t nextState);
	void ChangeStateIdle();
public:
	HarmFish(Player& player, Camera& camera, Vector2 spawnPos);
	void Update() override;
	void Draw() const override;
};

