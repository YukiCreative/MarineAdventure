#pragma once
#include "Vector2.h"

/// <summary>
///  ���������������ǂ肽��
///  ���x�������Ă��āA���W�����Ƃ�����
/// </summary>
class Rigid
{
private:
	Vector2 m_force;
	Vector2 m_accel;
	Vector2 m_position;
	Vector2 m_velocity;
	float m_weight;

	// �֐��|�C���^�g����
	using UpdateFunc_t = void (Rigid::*)();

	UpdateFunc_t m_updateFunc;

public:
	Rigid();
	/// <summary>
	/// �K�v�Ȓl�������l�ɓ��ꂽ�R���X�g���N�^
	/// </summary>
	/// <param name="weight"></param>
	Rigid(Vector2 initPos, float weight);

	/// <summary>
	/// �����̍X�V
	/// ���̊֐��ŁA���x�ɉ����Ė��t���[�����W���ړ���������A
	/// ���̑��x���R�ɂ���Č��炵���肷��
	/// </summary>
	void Update();

	// �������ƒn�㎞�Ŋ֐���؂�ւ���
	void WaterUpdate();
	void GroundUpdate();

	/// <summary>
	/// �͂�������
	/// </summary>
	/// <param name="_force">��</param>
	void AddForce(Vector2 force);

	/// <summary>
	/// �����̍��W��Ԃ�
	/// </summary>
	/// <returns>Vector2�^�̍��W</returns>
	Vector2 GetPos() { return m_position; }
};

