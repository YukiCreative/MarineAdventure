#include "Physics.h"
#include "Time.h"
#include <DxLib.h>

namespace
{
	// �d��
	// �Ƃ肠����9.8��
	constexpr float kGravity = 9.8f;
	// ���͂Ƃ����������
	Vector2 kFloatForce = Vector2(0.0f, -9.5f);
	// ��C��R
	constexpr float kAirResistance = 0.01f;
	// ���̒�R
	constexpr float kWaterResistance = 1.0f;
}

Physics::Physics() :
	m_accel(),
	m_weight(1.0f),
	m_volume(1.0f),
	m_addForce(),
	m_velocity(),
	m_updateFunc(&Physics::WaterUpdate) // �e�X�g
{
}

Physics::Physics(float weight, float volume) :
	m_accel(),
	m_weight(weight),
	m_volume(volume),
	m_addForce(),
	m_velocity(),
	m_updateFunc(&Physics::WaterUpdate) // �e�X�g
{
}

Vector2 Physics::Update()
{
	// �֐��|�C���^�𑖂点����I
	return (this->*m_updateFunc)();
}

Vector2 Physics::WaterUpdate()
{
	// �d�͉����x��͂ɉ��Z
	Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);

	// ��R���o��
	// ���̒�R�Ōv�Z
	Vector2 resistanceForce = m_velocity * kWaterResistance * -1;
	// �o�Ă����l��force���v�Z(���͂��l��)
	Vector2 m_force = (m_addForce + gravityForce + resistanceForce + kFloatForce * m_volume) * Time::DeltaTime();

	// F��m����Aa���o��
	// F = ma���Aa = F / m;
	// ����Z����̂��[
	m_accel = m_force / m_weight;

	// accel����velocity�ɉ��Z����
	m_velocity += m_accel;

	// m_addForce�����Z�b�g
	m_addForce = Vector2();

	// ���x�Ԃ�
	return m_velocity;
}

Vector2 Physics::GroundUpdate()
{
	// �d�͉����x��͂ɉ��Z
	Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);

	// ��R���o��
	// ��C��R�Ōv�Z
	Vector2 resistanceForce = m_velocity * kAirResistance;
	// �o�Ă����l��force����߂�
	Vector2 m_force = (m_addForce + gravityForce - resistanceForce)* Time::DeltaTime();

	// F��m����Aa���o��
	// F = ma���Aa = F / m;
	// ����Z����̂��[
	m_accel = m_force / m_weight;

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