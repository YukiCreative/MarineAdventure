#pragma once
#include "Vector2.h"

class CircleCollider;
class BoxCollider;

/// <summary>
/// �����蔻��������ǂ���N���X
/// �R���C�_�[�̑��΍��W�������Ă���
/// </summary>
class Collider
{
protected:
	/// <summary>
	/// �R���C�_�[�̑��΍��W
	/// Draw������W���炸�炷�����Ŏg��
	/// </summary>
	Vector2 m_posOffset;

public:

	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="other">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(CircleCollider other) = 0;
	/// <summary>
	/// �����蔻��̎擾(�΋�`)
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(BoxCollider other) = 0;
};

