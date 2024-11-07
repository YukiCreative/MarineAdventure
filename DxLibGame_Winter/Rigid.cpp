#include "Rigid.h"
#include "Time.h"

namespace
{
	// �d��
	// �Ƃ肠����9.8��
	constexpr float kGravity = 9.8f;
	// ��C��R
	constexpr float kAirResistance = 1.0;
	// ���̒�R
	constexpr float kWaterResistance = 0.01f;
}

Rigid::Rigid() :
	m_accel(),
	m_position(),
	m_weight(1.0f),
	m_force(),
	m_velocity(),
	m_updateFunc(&Rigid::WaterUpdate) // �e�X�g
{
}

Rigid::Rigid(Vector2 initPos, float weight) :
	m_accel(),
	m_position(initPos),
	m_weight(weight),
	m_force(),
	m_velocity(),
	m_updateFunc(&Rigid::WaterUpdate) // �e�X�g
{
}

void Rigid::Update()
{
	// �֐��|�C���^�𑖂点����I
	(this->*m_updateFunc)();
}

void Rigid::WaterUpdate()
{
	// �d�͉����x��F�ɂ��ĉ��Z
	Vector2 gravityForce = Vector2(0.0f, kGravity);
	m_force += gravityForce;

	// ��R���o��
	// ���̒�R�Ōv�Z
	Vector2 resistanceForce = m_velocity * kWaterResistance;
	// �o�Ă����l��force����߂�
	m_force -= resistanceForce;

	// F��m����Aa���o��
	// F = ma���Aa = F / m;
	// ����Z����̂��[
	m_accel = m_force / m_weight;

	// accel����velocity�ɉ��Z����
	m_velocity += m_accel;

	// �Ō�ɁAvelocity����position���ړ�
	m_position += m_velocity * Time::DeltaTime();
}

void Rigid::GroundUpdate()
{
	// �d�͉����x��F�ɂ��ĉ��Z
	Vector2 gravityForce = Vector2(0.0f, kGravity);
	m_force += gravityForce;

	// ��R���o��
	// ��C��R�Ōv�Z
	Vector2 resistanceForce = m_velocity * kAirResistance;
	// �o�Ă����l��force����߂�
	m_force -= resistanceForce;

	// F��m����Aa���o��
	// F = ma���Aa = F / m;
	// ����Z����̂��[
	m_accel = m_force / m_weight;

	// accel����velocity�ɉ��Z����
	m_velocity += m_accel;

	// �Ō�ɁAvelocity����position���ړ�
	m_position += m_velocity;
}

void Rigid::AddForce(Vector2 force)
{
	m_force += force;
}
