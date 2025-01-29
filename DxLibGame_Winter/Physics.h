#pragma once
#include "Vector2.h"
#include <memory>
#include "MapConstants.h"
#include <array>
#include <list>

class kMapChip;

/// <summary>
/// ���������������ǂ�
/// </summary>
class Physics
{
private:
	/// <summary>
	/// ������ꂽ��
	/// </summary>
	Vector2 m_addForce;
	Vector2 m_accel;
	Vector2 m_velocity;
	float m_weight;
	/// <summary>
	/// ���̂̑̐�
	/// ������g���ĕ��͂��Z�o
	/// </summary>
	float m_volume;
	bool m_useConstantForce;
	// �ڒn���Ă��邩
	// �{���͋󒆂ƒn��ŏ�Ԋ֐��𕪂���ׂ��Ȃ̂ł����A�ύX�ӏ����c��Ȃ̂�GroundUpdate���ŕ��򂵂܂�
	// �ǂ����Ă����Ȃ���
	bool m_isGrounded;

	// �֐��|�C���^�g����
	using UpdateState_t = Vector2(Physics::*)();
	UpdateState_t m_updateState;
	std::array<UpdateState_t, static_cast<int>(MapConstants::kEnvironment::kEnvNum)> m_stateArray =
	{
		&Physics::WaterUpdate,
		&Physics::GroundUpdate,
	};

	// �������ƒn�㎞�Ŋ֐���؂�ւ���
	Vector2 WaterUpdate();
	Vector2 GroundUpdate();
public:
	Physics();
	// �K�v�Ȓl�������l�ɓ��ꂽ�R���X�g���N�^
	Physics(float weight, float volume);

	// ���̊֐��ŁA�����̎����Ă���p�����[�^�ƁA���̃t���[���ɗ^����ꂽ�͂���
	// ������1�t���[���ɓ����������Z�o����B
	Vector2 Update();

	// �͂�������
	void AddForce(Vector2 force);

	/// �����ʂ葬�x��Ԃ�
	Vector2 GetVel() const { return m_velocity; }

	/// <summary>
	/// �ړ����~�߂�
	/// ����ȊO�Œ���velocity��������̂͂ł��邾����߂悤
	/// </summary>
	void Stop() { m_velocity = Vector2::Zero(); }
	void StopY() { m_velocity.y = 0; }
	/// <summary>
	/// �d�͂ƕ��͂̂����������痣�ꂽ���Ƃ���
	/// </summary>
	void UseConstantForce(bool value) { m_useConstantForce = value; }

	// �^����ꂽ�񋓂ɑΉ�������Ԃ��ǂ�����Ԃ�
	bool CheckState(const MapConstants::kEnvironment&) const;
	void ChangeState(const MapConstants::kEnvironment&);
	void InvertState();
	MapConstants::kEnvironment GetNowEnvironment() const;
	void IsGrounded(const bool& value) { m_isGrounded = value; }
};