#include "Physics.h"
#include "Time.h"
#include <DxLib.h>

namespace
{
	// �d��
	constexpr float kGravity = 1.0f;
	// ���͂Ƃ����������
	Vector2 kFloatForce = Vector2(0.0f, -0.98f);
	// ��C��R
	constexpr float kAirResistance = 0.1f;
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
	m_updateFunc(&Physics::WaterUpdate) // �e�X�g
{
}

Physics::Physics(float weight, float volume) :
	m_accel(),
	m_weight(weight),
	m_volume(volume),
	m_useConstantForce(true),
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
	Vector2 resistanceForce = m_velocity * kWaterResistance * -1.0f;
	// �o�Ă����l��force���v�Z(���͂��l��)
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
	// �d�́A���͂̏���
	if (m_useConstantForce)
	{
		// �d�͉����x��͂ɉ��Z
		Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);
		force += gravityForce;
	}

	// ��R���o��
	// ��C��R�Ōv�Z
	Vector2 resistanceForce = m_velocity * kAirResistance;
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