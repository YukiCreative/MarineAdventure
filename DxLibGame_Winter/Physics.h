#pragma once
#include "Vector2.h"
#include <memory>

class MapChip;

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

	// �֐��|�C���^�g����
	using UpdateFunc_t = Vector2 (Physics::*)();

	UpdateFunc_t m_updateFunc;

public:
	Physics();
	/// <summary>
	/// �K�v�Ȓl�������l�ɓ��ꂽ�R���X�g���N�^
	/// </summary>
	/// <param name="weight"></param>
	Physics(float weight, float volume);

	/// <summary>
	/// �����̍X�V
	/// ���̊֐��ŁA�����̎����Ă���p�����[�^�ƁA���̃t���[���ɗ^����ꂽ�͂���
	/// ������1�t���[���ɓ����������Z�o����B
	/// </summary>
	Vector2 Update();

	// �������ƒn�㎞�Ŋ֐���؂�ւ���
	Vector2 WaterUpdate();
	Vector2 GroundUpdate();

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
	void Stop() { m_velocity = Vector2(); }
};


