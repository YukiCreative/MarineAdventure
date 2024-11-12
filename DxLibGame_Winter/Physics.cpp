#include "Physics.h"
#include "Time.h"
#include <DxLib.h>

namespace
{
	// 重力
	// とりあえず9.8で
	constexpr float kGravity = 9.8f;
	// 浮力とかつけちゃって
	Vector2 kFloatForce = Vector2(0.0f, -9.5f);
	// 空気抵抗
	constexpr float kAirResistance = 0.01f;
	// 水の抵抗
	constexpr float kWaterResistance = 1.0f;
}

Physics::Physics() :
	m_accel(),
	m_weight(1.0f),
	m_volume(1.0f),
	m_addForce(),
	m_velocity(),
	m_updateFunc(&Physics::WaterUpdate) // テスト
{
}

Physics::Physics(float weight, float volume) :
	m_accel(),
	m_weight(weight),
	m_volume(volume),
	m_addForce(),
	m_velocity(),
	m_updateFunc(&Physics::WaterUpdate) // テスト
{
}

Vector2 Physics::Update()
{
	// 関数ポインタを走らせるんや！
	return (this->*m_updateFunc)();
}

Vector2 Physics::WaterUpdate()
{
	// 重力加速度を力に加算
	Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);

	// 抵抗を出す
	// 水の抵抗で計算
	Vector2 resistanceForce = m_velocity * kWaterResistance * -1;
	// 出てきた値でforceを計算(浮力を考慮)
	Vector2 m_force = (m_addForce + gravityForce + resistanceForce + kFloatForce * m_volume) * Time::DeltaTime();

	// Fとmから、aを出す
	// F = maより、a = F / m;
	// 割り算するのかー
	m_accel = m_force / m_weight;

	// accelからvelocityに加算する
	m_velocity += m_accel;

	// m_addForceをリセット
	m_addForce = Vector2();

	// 速度返す
	return m_velocity;
}

Vector2 Physics::GroundUpdate()
{
	// 重力加速度を力に加算
	Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);

	// 抵抗を出す
	// 空気抵抗で計算
	Vector2 resistanceForce = m_velocity * kAirResistance;
	// 出てきた値でforceを弱める
	Vector2 m_force = (m_addForce + gravityForce - resistanceForce)* Time::DeltaTime();

	// Fとmから、aを出す
	// F = maより、a = F / m;
	// 割り算するのかー
	m_accel = m_force / m_weight;

	// accelからvelocityに加算する
	m_velocity += m_accel;

	// m_addForceをリセット
	m_addForce = Vector2();

	// 最後に速度を返す
	return m_velocity;
}

void Physics::AddForce(Vector2 force)
{
	// 一回addForceに力をためておく
	m_addForce += force;
}