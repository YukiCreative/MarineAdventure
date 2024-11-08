#include "Physics.h"
#include "Time.h"
#include <DxLib.h>

namespace
{
	// �d��
	// �Ƃ肠����9.8��
	constexpr float kGravity = 9.8f;
	// ���͂Ƃ����������
	constexpr float kFloatForce = 5.0f;
	// ��C��R
	constexpr float kAirResistance = 0.01f;
	// ���̒�R
	constexpr float kWaterResistance = 0.15f;
}

Physics::Physics() :
	m_accel(),
	m_position(),
	m_weight(1.0f),
	m_addForce(),
	m_velocity(),
	m_updateFunc(&Physics::WaterUpdate) // �e�X�g
{
}

Physics::Physics(Vector2 initPos, float weight) :
	m_accel(),
	m_position(initPos),
	m_weight(weight),
	m_addForce(),
	m_velocity(),
	m_updateFunc(&Physics::WaterUpdate) // �e�X�g
{
}

void Physics::Update()
{
	// �֐��|�C���^�𑖂点����I
	(this->*m_updateFunc)();
}

void Physics::WaterUpdate()
{
	// �d�͉����x��͂ɉ��Z
	Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);

	// ��R���o��
	// ���̒�R�Ōv�Z
	Vector2 resistanceForce = m_velocity * kWaterResistance;
	// �o�Ă����l��force���v�Z
	Vector2 m_force = m_addForce + gravityForce - resistanceForce;

	// F��m����Aa���o��
	// F = ma���Aa = F / m;
	// ����Z����̂��[
	m_accel = m_force / m_weight;

	// accel����velocity�ɉ��Z����
	m_velocity += m_accel;

	// �Ō�ɁAvelocity����position���ړ�
	m_position += m_velocity * Time::DeltaTime();

	// ������ƃe�X�g�Ńf�o�b�O�\��
	DrawFormatString(0, 30, 0xffffff, "accel x = %f, accel y = %f", m_accel.x, m_accel.y);
	DrawFormatString(0, 45, 0xffffff, "velocity x = %f, velocity y = %f", m_velocity.x, m_velocity.y);

	// m_addForce�����Z�b�g
	m_addForce = Vector2();
}

void Physics::GroundUpdate()
{
	// �d�͉����x��͂ɉ��Z
	Vector2 gravityForce = Vector2(0.0f, kGravity * m_weight);

	// ��R���o��
	// ���̒�R�Ōv�Z
	Vector2 resistanceForce = m_velocity * kAirResistance;
	// �o�Ă����l��force����߂�
	Vector2 m_force = m_addForce + gravityForce - resistanceForce;

	// F��m����Aa���o��
	// F = ma���Aa = F / m;
	// ����Z����̂��[
	m_accel = m_force / m_weight;

	// accel����velocity�ɉ��Z����
	m_velocity += m_accel;

	// �Ō�ɁAvelocity����position���ړ�
	m_position += m_velocity;
}

void Physics::AddForce(Vector2 force)
{
	// ���addForce�ɗ͂����߂Ă���
	m_addForce += force;
}
