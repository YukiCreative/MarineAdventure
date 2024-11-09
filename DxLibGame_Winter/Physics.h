#pragma once
#include "Vector2.h"

/// <summary>
///  ���������������ǂ肽��
///  ���x�������Ă��āA���W�����Ƃ�����
/// </summary>
class Physics
{
private:
	/// <summary>
	/// ������ꂽ��
	/// </summary>
	Vector2 m_addForce;
	Vector2 m_accel;
	Vector2 m_position;
	Vector2 m_velocity;
	float m_weight;
	/// <summary>
	/// ���̂̑̐�
	/// ������g���ĕ��͂��Z�o
	/// </summary>
	float m_volume;

	// �֐��|�C���^�g����
	using UpdateFunc_t = void (Physics::*)();

	UpdateFunc_t m_updateFunc;

public:
	Physics();
	/// <summary>
	/// �K�v�Ȓl�������l�ɓ��ꂽ�R���X�g���N�^
	/// </summary>
	/// <param name="weight"></param>
	Physics(Vector2 initPos, float weight, float volume);

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


