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
	// �I�u�W�F�N�g���ǂ̌����ɂǂꂭ�炢������Ă��邩
	std::list<Vector2> m_pushedForces;

	// �֐��|�C���^�g����
	using UpdateState_t = Vector2 (Physics::*)();
	UpdateState_t m_updateState;
	std::array<UpdateState_t, static_cast<int>(MapConstants::Environment::kEnvNum)> m_stateArray = 
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
	/// <summary>
	/// �d�͂ƕ��͂̂����������痣�ꂽ���Ƃ���
	/// </summary>
	void UseConstantForce(bool value) { m_useConstantForce = value; }

	// �^����ꂽ�񋓂ɑΉ�������Ԃ��ǂ�����Ԃ�
	bool CheckState (const MapConstants::Environment&) const;
	void ChangeState(const MapConstants::Environment&);
	void InvertState();
	MapConstants::Environment GetNowEnvironment() const;
	// �������疀�C�͂��Z�o���āA�ړ����ɍl������
	// ������Physics��Update�̑O�Ɏ��s���Ȃ��ƌ��ʂ��Ȃ�����
	// �������F�����́@�������F���C�萔(0�Ŗ��C�Ȃ��A�}�C�i�X���Ƌt�����ɖ��C������)
	void AddFrictionalForce(const Vector2& pushForce, const float& frictionFactor);
};