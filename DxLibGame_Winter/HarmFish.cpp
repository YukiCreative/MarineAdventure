#include "HarmFish.h"
#include <DxLib.h>
#include "Camera.h"
#include <memory>
#include "Physics.h"
#include "Player.h"
#include "CircleCollider.h"

namespace
{
	constexpr int kInitHp = 2;
	constexpr float kRadius = 20.0f;
	constexpr int kDamageMortionFrame = 60;
}

void HarmFish::Idle()
{
	// 待機モーション実行
	// Playerとの接触判定をする
	CollisionStatus collision = m_collider->CheckHit(m_playerRef.GetCollider());
	if (collision.isCollide)
	{
		// もしPlayerの状態が攻撃状態なら
		if (m_playerRef.CheckState(PlayerState::kAttack) || m_playerRef.CheckState(PlayerState::kStrongAttack))
		{
			// ここでHPを減らす
			--m_hp;
			printf("HP%dになたよ", m_hp);
			m_graphic = ">_<";
			m_state = &HarmFish::Damage;
			// プレイヤーに「攻撃した」と教える
			m_playerRef.OnAttack();
		}
		else
		{
			// ここでプレイヤーにダメージを教えてあげる
			m_playerRef.OnDamage();
		}
		// プレイヤーをぶっ飛ばす
		m_playerRef.Stop();
		m_playerRef.AddForce(-collision.overlap.GetNormalize());
	}
}

void HarmFish::Damage()
{
	++m_stateFrameCount;
	if (m_hp <= 0)
	{
		m_stateFrameCount = 0;
		printf("ちんだ");
		m_graphic = "o_o";
		m_state = &HarmFish::Death;
		return;
	}
	// アニメーションしたい
	// 0になったらDeath
	if (m_stateFrameCount > kDamageMortionFrame)
	{
		m_stateFrameCount = 0;
		m_graphic = "^_^";
		m_state = &HarmFish::Idle;
		(this->*m_state)();
		return;
	}
}

void HarmFish::Death()
{
	++m_stateFrameCount;
	if (m_stateFrameCount > kDamageMortionFrame)
	{
		// 消える
		m_isDeleted = true;
		return;
	}
}

HarmFish::HarmFish(Player& player, Camera& camera, Vector2 spawnPos) :
	Enemy(player, camera, spawnPos),
	m_state(&HarmFish::Idle),
	m_stateFrameCount(0),
	m_graphic("^_^")
{
	// 生焼けになるけど大丈夫かな
	m_physics = std::make_shared<Physics>(1.0f, 1.0f);
	m_physics->UseConstantForce(false);
	m_collider = std::make_shared<CircleCollider>(m_pos, kRadius);
	m_hp = kInitHp;
}

void HarmFish::Update()
{
	// 状態に応じた処理を
	(this->*m_state)();

	m_pos += m_physics->Update();

	// Updateの結果、画面外に出たら死亡
	if (CheckScreenOut())
	{
		m_isDeleted = true;
	}
}

void HarmFish::Draw() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(kRadius), 0x0000ff);
	int width = GetDrawStringWidth(m_graphic.c_str(), static_cast<int>(m_graphic.size()));
	DrawFormatString(static_cast<int>(screenPos.x - width * 0.5f), static_cast<int>(screenPos.y) - 5, 0xffffff, m_graphic.c_str());
}