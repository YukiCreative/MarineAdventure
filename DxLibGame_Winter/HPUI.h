#pragma once
#include <array>
#include <memory>
#include "GameObject.h"

class Animation;

// UI
// 現在体力を現すハート一つ分
class HitPointHeart : public GameObject
{
private:
	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_fullAnim;
	std::shared_ptr<Animation> m_emptyAnim;
	std::shared_ptr<Animation> m_damageAnim;

	using State_t = void (HitPointHeart::*)();
	State_t m_state;

	bool m_isFull;

	// 満たされている状態と空の状態は同じ状態で管理してます
	void Normal();
	void Damage();
public:
	HitPointHeart(const Vector2& initPos);

	void Update() override;
	void Draw() const override;

	// ダメージを受けたときに
	void OnDamage();
	bool IsFull() const { return m_isFull; }

	void OnRecovery();
};

namespace
{
	constexpr int kMaxHitPoint = 5;
}

// ハートをまとめて実行する
// 増やしたり、減らしたり
class HitPoints : public GameObject
{
private:
	// どうせ最大HP変わらないのでArray
	std::array<std::shared_ptr<HitPointHeart>, kMaxHitPoint> m_hearts;
public:
	HitPoints(const Vector2& initPos);

	void Update() override;
	void Draw() const override;

	// プレイヤーから呼ぶ
	void OnDamage(const int damageAmount = 1);
	void OnRecovery(const int recoverAmount = 1);
};