#pragma once
#include "Vector2.h"

class CircleCollider;
class BoxCollider;

/// <summary>
/// �����蔻��������ǂ���N���X
/// </summary>
class Collider
{
protected:
	/// <summary>
	/// �R���C�_�[�̑��΍��W
	/// Draw������W���炸�炷�����Ŏg��
	/// </summary>
	Vector2 m_posOffset;

	/// <summary>
	/// �������A�^�b�`����Ă���I�u�W�F�N�g�̍��W���Q��
	/// </summary>
	Vector2& m_pos;
public:
	Collider(Vector2& pos);

	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="other">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(CircleCollider& other) = 0;
	/// <summary>
	/// �����蔻��̎擾(�΋�`)
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHit(BoxCollider& other) = 0;

	void SetOffset(Vector2 value) { m_posOffset = value; }
	Vector2 GetPos() { return m_pos; }
};

