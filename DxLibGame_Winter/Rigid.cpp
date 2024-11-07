#include "Rigid.h"
#include "Time.h"
#include <DxLib.h>

namespace
{
	// 重力
	// とりあえず9.8で
	constexpr float kGravity = 9.8f;
	// 空気抵抗
	constexpr float kAirResistance = 0.01f;
	// 水の抵抗
	constexpr float kWaterResistance = 0.5f;
}

Rigid::Rigid() :
	m_accel(),
	m_position(),
	m_weight(1.0f),
	m_force(),
	m_velocity(),
	m_updateFunc(&Rigid::WaterUpdate) // テスト
{
}

Rigid::Rigid(Vector2 initPos, float weight) :
	m_accel(),
	m_position(initPos),
	m_weight(weight),
	m_force(),
	m_velocity(),
	m_updateFunc(&Rigid::WaterUpdate) // テスト
{
}

void Rigid::Update()
{
	// 関数ポインタを走らせるんや！
	(this->*m_updateFunc)();
}

void Rigid::WaterUpdate()
{
	// 重力加速度を力に加算
	Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);

	// 抵抗を出す
	// 水の抵抗で計算
	Vector2 resistanceForce = m_velocity * kWaterResistance;
	// 出てきた値でforceを弱める
	m_force = gravityForce - resistanceForce;

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
}

void Rigid::GroundUpdate()
{
	// 重力加速度をFにして加算
	Vector2 gravityForce = Vector2(0.0f, kGravity);
	m_force += gravityForce;

	// 抵抗を出す
	// 空気抵抗で計算
	Vector2 resistanceForce = m_velocity * kAirResistance;
	// 出てきた値でforceを弱める
	m_force -= resistanceForce;

	// Fとmから、aを出す
	// F = maより、a = F / m;
	// 割り算するのかー
	m_accel = m_force / m_weight;

	// accelからvelocityに加算する
	m_velocity += m_accel;

	// 最後に、velocityからpositionを移動
	m_position += m_velocity;
}

void Rigid::AddForce(Vector2 force)
{
	m_force += force;
}
