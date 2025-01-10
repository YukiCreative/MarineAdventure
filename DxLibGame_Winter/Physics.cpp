#include "Physics.h"
#include "Time.h"
#include <DxLib.h>

namespace
{
	// 重力
	constexpr float kGravity = 0.5f;
	// 浮力とかつけちゃって
	Vector2 kFloatForce = Vector2(0.0f, -0.52f);
	// 空気抵抗
	constexpr float kAirResistance = 0.008f;
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
	m_updateState(&Physics::WaterUpdate) // テスト
{
}

Physics::Physics(float weight, float volume) :
	m_accel(),
	m_weight(weight),
	m_volume(volume),
	m_useConstantForce(true),
	m_addForce(),
	m_velocity(),
	m_updateState(&Physics::GroundUpdate) // テスト
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
	Vector2 resistanceForce = m_velocity * kWaterResistance * -1.0f;
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

	// 摩擦力の力を削除
	m_pushedForces.clear();

	// 速度返す
	return m_velocity;
}

Vector2 Physics::GroundUpdate()
{
	// とりま加えられた力で初期化
	Vector2 force = m_addForce;
	// 重力、浮力の処理
	if (m_useConstantForce)
	{
		// 重力加速度を力に加算
		Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);
		force += gravityForce;
	}

	// 抵抗を出す
	// 空気抵抗で計算
	Vector2 resistanceForce = m_velocity * kAirResistance;
	// 出てきた値でforceを弱める
	force += resistanceForce;

	// 押されている力に垂直な向きでforceを弱める
	// 弱めすぎてマイナスにはならない
	for (const auto& pushedForce : m_pushedForces)
	{
		//pushedForce
	}

	// Fとmから、aを出す
	// F = maより、a = F / m;
	// 割り算するのかー
	m_accel = force / m_weight;

	// accelからvelocityに加算する
	m_velocity += m_accel;

	// m_addForceをリセット
	m_addForce = Vector2();

	// 摩擦力の力を削除
	m_pushedForces.clear();

	// 最後に速度を返す
	return m_velocity;
}

void Physics::AddForce(Vector2 force)
{
	// 一回addForceに力をためておく
	m_addForce += force;
}

bool Physics::CheckState(const MapConstants::Environment& env) const
{
	return m_stateArray[static_cast<int>(env)] == m_updateState;
}

void Physics::ChangeState(const MapConstants::Environment& env)
{
	m_updateState = m_stateArray[static_cast<int>(env)];
}

void Physics::InvertState()
{
	// 状態は地上と水中の二つしかないとする
	// 仕様追加時は頑張れ
	if (CheckState(MapConstants::Environment::kGround))
	{
		m_updateState = &Physics::WaterUpdate;
	}
	else
	{
		m_updateState = &Physics::GroundUpdate;
	}
}

MapConstants::Environment Physics::GetNowEnvironment() const
{
	if (m_updateState == &Physics::GroundUpdate)
	{
		return MapConstants::Environment::kGround;
	}
	else
	{
		return MapConstants::Environment::kWater;
	}
}

void Physics::AddFrictionalForce(const Vector2& pushForce, const float& frictionFactor)
{
	m_pushedForces.push_back(pushForce * frictionFactor);
}