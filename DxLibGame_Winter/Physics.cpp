#include "Physics.h"
#include "Time.h"
#include <cmath>

namespace
{
	// 重力
	constexpr float kGravity = 0.5f;
	// 浮力とかつけちゃって
	Vector2 kFloatForce = Vector2(0.0f, -0.52f);
	// 空気抵抗
	constexpr float kAirResistance = 0.0001f;
	constexpr float kGroundResistance = 0.05f;
	// 水の抵抗
	constexpr float kWaterResistance = 0.03f;
}

Physics::Physics() :
	m_accel(),
	m_weight(1.0f),
	m_volume(1.0f),
	m_useConstantForce(true),
	m_addForce(),
	m_velocity(),
	m_updateState(&Physics::WaterUpdate), // テスト
	m_isGrounded(false)
{
}

Physics::Physics(float weight, float volume) :
	m_accel(),
	m_weight(weight),
	m_volume(volume),
	m_useConstantForce(true),
	m_addForce(),
	m_velocity(),
	m_updateState(&Physics::WaterUpdate), // テスト
	m_isGrounded(false)
{
}

Vector2 Physics::Update()
{
	// 関数ポインタを走らせるんや！
	return (this->*m_updateState)();
}

Vector2 Physics::WaterUpdate()
{
	// とりま加えられた力で初期化
	Vector2 force = m_addForce;
	if (m_useConstantForce)
	{
		// 重力加速度を力に加算
		Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);
		// 浮力
		Vector2 floatForce = kFloatForce * m_volume;
		force += gravityForce + floatForce;
	}

	// 抵抗を出す
	// 水の抵抗で計算
	Vector2 resistanceForce = -m_velocity * kWaterResistance;
	// 出てきた値でforceを計算
	force += resistanceForce;

	// Fとmから、aを出す
	// F = maより、a = F / m;
	// 割り算するのかー
	m_accel = force / m_weight;

	// accelからvelocityに加算する
	m_velocity += m_accel;

	// m_addForceをリセット
	m_addForce = Vector2();

	// 速度返す
	return m_velocity;
}

Vector2 Physics::GroundUpdate()
{
	// とりま加えられた力で初期化
	Vector2 force = m_addForce;
	// 重力の処理
	if (m_useConstantForce)
	{
		// 重力加速度を力に加算
		Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);
		force += gravityForce;
	}

	// 抵抗を出す
	// 接地しているかしていないかで分ける
	const float& resistance = m_isGrounded ? kGroundResistance : kAirResistance;
	Vector2 resistanceForce = -m_velocity * resistance;
	// 出てきた値でforceを弱める
	force += resistanceForce;

	// Fとmから、aを出す
	// F = maより、a = F / m;
	// 割り算するのかー
	m_accel = force / m_weight;

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

bool Physics::CheckState(const MapConstants::kEnvironment& env) const
{
	return m_stateArray[static_cast<int>(env)] == m_updateState;
}

void Physics::ChangeState(const MapConstants::kEnvironment& env)
{
	m_updateState = m_stateArray[static_cast<int>(env)];
}

void Physics::InvertState()
{
	// 状態は地上と水中の二つしかないとする
	// 仕様追加時は頑張れ
	if (CheckState(MapConstants::kEnvironment::kGround))
	{
		m_updateState = &Physics::WaterUpdate;
	}
	else
	{
		m_updateState = &Physics::GroundUpdate;
	}
}

MapConstants::kEnvironment Physics::GetNowEnvironment() const
{
	if (m_updateState == &Physics::GroundUpdate)
	{
		return MapConstants::kEnvironment::kGround;
	}
	else
	{
		return MapConstants::kEnvironment::kWater;
	}
}