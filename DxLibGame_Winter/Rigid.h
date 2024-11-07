#pragma once
#include "Vector2.h"

/// <summary>
///  ���������������ǂ肽��
///  ���x�������Ă��āA���W�����Ƃ�����
/// </summary>
class Rigid
{
private:
	Vector2 force;
	Vector2 accel;
	Vector2 position;
	float weight;
	/// <summary>
	/// �����ړ����̒�R
	/// </summary>
	float waterResistance;
	float airResistance;
public:
	Rigid();

	/// <summary>
	/// �����̍X�V
	/// ���̊֐��ŁA���x�ɉ����Ė��t���[�����W���ړ���������A
	/// ���̑��x���R�ɂ���Č��炵���肷��
	/// </summary>
	void Update();
};

