#include "HarmFish.h"
#include <DxLib.h>
#include "Camera.h"
#include <memory>
#include "Physics.h"

namespace
{
	constexpr int kRadius = 20;
}

void HarmFish::Idle()
{
	// 待機モーション実行
	// Playerとの接触判定をする
	//if ()
	// 攻撃状態のプレイヤーに触れたらDamage
}

void HarmFish::Damage()
{
	// hp減らす
	// 0になったらDeath
}

void HarmFish::Death()
{
	// 消える
	// Enemyを管理してるクラスに問い合わせて消してもらう感じにしようかな
}

HarmFish::HarmFish(Camera& camera) :
	Enemy(camera),
	m_state(&HarmFish::Idle)
{
	// 生焼けになるけど大丈夫かな
	m_physics = std::make_shared<Physics>(1.0f, 1.0f);
	m_physics->UseConstantForce(false);
}

void HarmFish::Update()
{
	// 状態に応じた処理を
	(this->*m_state)();

	m_pos += m_physics->Update();
}

void HarmFish::Draw()
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), kRadius, 0x0000ff);
}