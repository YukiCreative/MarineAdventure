#include "Physics.h"
#include "Time.h"
#include <cmath>

namespace
{
	// �d��
	constexpr float kGravity = 0.5f;
	// ���͂Ƃ����������
	Vector2 kFloatForce = Vector2(0.0f, -0.52f);
	// ��C��R
	constexpr float kAirResistance = 0.0001f;
	constexpr float kGroundResistance = 0.05f;
	// ���̒�R
	constexpr float kWaterResistance = 0.03f;
}

Physics::Physics() :
	m_accel(),
	m_weight(1.0f),
	m_volume(1.0f),
	m_useConstantForce(true),
	m_addForce(),
	m_velocity(),
	m_updateState(&Physics::WaterUpdate), // �e�X�g
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
	m_updateState(&Physics::WaterUpdate), // �e�X�g
	m_isGrounded(false)
{
}

Vector2 Physics::Update()
{
	// �֐��|�C���^�𑖂点����I
	return (this->*m_updateState)();
}

Vector2 Physics::WaterUpdate()
{
	// �Ƃ�܉�����ꂽ�͂ŏ�����
	Vector2 force = m_addForce;
	if (m_useConstantForce)
	{
		// �d�͉����x��͂ɉ��Z
		Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);
		// ����
		Vector2 floatForce = kFloatForce * m_volume;
		force += gravityForce + floatForce;
	}

	// ��R���o��
	// ���̒�R�Ōv�Z
	Vector2 resistanceForce = -m_velocity * kWaterResistance;
	// �o�Ă����l��force���v�Z
	force += resistanceForce;

	// F��m����Aa���o��
	// F = ma���Aa = F / m;
	// ����Z����̂��[
	m_accel = force / m_weight;

	// accel����velocity�ɉ��Z����
	m_velocity += m_accel;

	// m_addForce�����Z�b�g
	m_addForce = Vector2();

	// ���x�Ԃ�
	return m_velocity;
}

Vector2 Physics::GroundUpdate()
{
	// �Ƃ�܉�����ꂽ�͂ŏ�����
	Vector2 force = m_addForce;
	// �d�͂̏���
	if (m_useConstantForce)
	{
		// �d�͉����x��͂ɉ��Z
		Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);
		force += gravityForce;
	}

	// ��R���o��
	// �ڒn���Ă��邩���Ă��Ȃ����ŕ�����
	const float& resistance = m_isGrounded ? kGroundResistance : kAirResistance;
	Vector2 resistanceForce = -m_velocity * resistance;
	// �o�Ă����l��force����߂�
	force += resistanceForce;

	// F��m����Aa���o��
	// F = ma���Aa = F / m;
	// ����Z����̂��[
	m_accel = force / m_weight;

	// accel����velocity�ɉ��Z����
	m_velocity += m_accel;

	// m_addForce�����Z�b�g
	m_addForce = Vector2();

	// �Ō�ɑ��x��Ԃ�
	return m_velocity;
}

void Physics::AddForce(Vector2 force)
{
	// ���addForce�ɗ͂����߂Ă���
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
	// ��Ԃ͒n��Ɛ����̓�����Ȃ��Ƃ���
	// �d�l�ǉ����͊撣��
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