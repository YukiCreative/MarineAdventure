#include "Physics.h"
#include "Time.h"
#include <DxLib.h>

namespace
{
	// 重力
	// とりあえず9.8で
	constexpr float kGravity = 9.8f;
	// 浮力とかつけちゃって
	constexpr float kFloatForce = 5.0f;
	// 空気抵抗
	constexpr float kAirResistance = 0.01f;
	// 水の抵抗
	constexpr float kWaterResistance = 0.15f;
}

Physics::Physics() :
	m_accel(),
	m_position(),
	m_weight(1.0f),
	m_addForce(),
	m_velocity(),
	m_updateFunc(&Physics::WaterUpdate) // テスト
{
}

Physics::Physics(Vector2 initPos, float weight) :
	m_accel(),
	m_position(initPos),
	m_weight(weight),
	m_addForce(),
	m_velocity(),
	m_updateFunc(&Physics::WaterUpdate) // テスト
{
}

void Physics::Update()
{
	// 関数ポインタを走らせるんや！
	(this->*m_updateFunc)();
}

void Physics::WaterUpdate()
{
	// 重力加速度を力に加算
	Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);

	// 抵抗を出す
	// 水の抵抗で計算
	Vector2 resistanceForce = m_velocity * kWaterResistance;
	// 出てきた値でforceを計算
	Vector2 m_force = m_addForce + gravityForce - resistanceForce;

	// Fとmから、aを出す
	// F = maより、a = F / m;
	// 割り算するのかー
	m_accel = m_force / m_weight;

	// accelからvelocityに加算する
	m_velocity += m_accel;

	// 最後に、velocityからpositionを移動
	m_position += m_velocity * Time::DeltaTime();

	// ちょっとテストでデバッグ表示
	DrawFormatString(0, 30, 0xffffff, "accel x = %f, accel y = %f", m_accel.x, m_accel.y);
	DrawFormatString(0, 45, 0xffffff, "velocity x = %f, velocity y = %f", m_velocity.x, m_velocity.y);

	// m_addForceをリセット
	m_addForce = Vector2();
}

void Physics::GroundUpdate()
{
	// 重力加速度を力に加算
	Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);

	// 抵抗を出す
	// 水の抵抗で計算
	Vector2 resistanceForce = m_velocity * kAirResistance;
	// 出てきた値でforceを弱める
	Vector2 m_force = m_addForce + gravityForce - resistanceForce;

	// Fとmから、aを出す
	// F = maより、a = F / m;
	// 割り算するのかー
	m_accel = m_force / m_weight;

	// accelからvelocityに加算する
	m_velocity += m_accel;

	// 最後に、velocityからpositionを移動
	m_position += m_velocity;
}

void Physics::AddForce(Vector2 force)
{
	// 一回addForceに力をためておく
	m_addForce += force;
}
