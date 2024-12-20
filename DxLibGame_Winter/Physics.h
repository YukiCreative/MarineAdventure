#pragma once
#include "Vector2.h"
#include <memory>
#include "MapConstants.h"
#include <array>

class kMapChip;

/// <summary>
///  ���������������ǂ�
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

	// �֐��|�C���^�g����
	using UpdateState_t = Vector2 (Physics::*)();
	UpdateState_t m_updateState;
	std::array<UpdateState_t, static_cast<int>(MapConstants::Environment::kEnvNum)> m_stateArray = 
	{
		&Physics::WaterUpdate,
		&Physics::GroundUpdate,
	};;

	// �������ƒn�㎞�Ŋ֐���؂�ւ���
	Vector2 WaterUpdate();
	Vector2 GroundUpdate();
public:
	Physics();
	/// <summary>
	/// �K�v�Ȓl�������l�ɓ��ꂽ�R���X�g���N�^
	/// </summary>
	/// <param name="weight">�d��</param>
	/// <param name="volume">�̐�</param>
	Physics(float weight, float volume);

	/// <summary>
	/// �����̍X�V
	/// ���̊֐��ŁA�����̎����Ă���p�����[�^�ƁA���̃t���[���ɗ^����ꂽ�͂���
	/// ������1�t���[���ɓ����������Z�o����B
	/// </summary>
	Vector2 Update();

	/// <summary>
	/// �͂�������
	/// </summary>
	/// <param name="_force">��</param>
	void AddForce(Vector2 force);

	/// <summary>
	/// �����ʂ葬�x��Ԃ�
	/// </summary>
	/// <returns>���݂̑��x</returns>
	Vector2 GetVel() const { return m_velocity; }

	/// <summary>
	/// �ړ����~�߂�
	/// ����ȊO�Œ���velocity��������̂͂ł��邾����߂悤
	/// </summary>
	void Stop() { m_velocity = Vector2::Zero(); }
	/// <summary>
	/// �d�͂ƕ��͂̂����������痣�ꂽ���Ƃ���
	/// </summary>
	void UseConstantForce(bool value) { m_useConstantForce = value; }

	// �^����ꂽ�񋓂ɑΉ�������Ԃ��ǂ�����Ԃ�
	bool CheckState(const MapConstants::Environment&);
	void ChangeState(const MapConstants::Environment&);
	void InvertState();
	MapConstants::Environment GetNowEnvironment();
};


