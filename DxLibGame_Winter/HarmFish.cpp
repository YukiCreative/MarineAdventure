#include "HarmFish.h"
#include <DxLib.h>
#include "Camera.h"
#include <memory>
#include "Physics.h"
#include "Player.h"
#include "CircleCollider.h"
#include "EnemyController.h"

namespace
{
	constexpr int kInitHp = 2;
	constexpr int kRadius = 20;
	constexpr int kDamageMortionFrame = 60;
}

void HarmFish::Idle()
{
	// 待機モーション実行
	// Playerとの接触判定をする
	if (m_collider->CheckHit(m_playerRef.GetCollider()))
	{
		// もしPlayerの状態が攻撃状態なら
		if (m_playerRef.CheckState(PlayerState::kAttack) || m_playerRef.CheckState(PlayerState::kStrongAttack))
		{
			// ここでHPを減らす
			--m_hp;
			printf("HP%dになたよ", m_hp);
			m_graphic = ">_<";
			m_state = &HarmFish::Damage;
			(this->*m_state)();
			return;
		}
		else
		{
			// ここでプレイヤーにダメージを教えてあげる
			//m_playerRef.
		}
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
		// Enemyを管理してるクラスに問い合わせて消してもらう感じにしようかな
		m_isDead = true;
		return;
	}
}

HarmFish::HarmFish(Player& player, Camera& camera, EnemyController& controller, Vector2 spawnPos) :
	Enemy(player, camera, controller, spawnPos),
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
		m_isDead = true;
	}
}

void HarmFish::Draw()
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), kRadius, 0x0000ff);
	int width = GetDrawStringWidth(m_graphic.c_str(), m_graphic.size());
	DrawFormatString(static_cast<int>(screenPos.x) - width * 0.5f, static_cast<int>(screenPos.y) - 5, 0xffffff, m_graphic.c_str());
}