#pragma once
#include "Vector2.h"
#include <memory>

class CircleCollider;
class BoxCollider;

enum class ColKind
{
	kCircle,
	kBox,
};

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

	const ColKind m_kind;

public:
	Collider(ColKind kind, Vector2& pos);

	void SetOffset(Vector2 value) { m_posOffset = value; }
	Vector2 GetPos() { return m_pos; }
	// �g���Ȃ�
	Vector2* GetPVec() { return &m_pos; }
	ColKind GetKind() { return m_kind; }

	bool CheckHit(std::shared_ptr<Collider> other);
	// Vector2�̎Q�Ƃ�n���Ă����Ώd�Ȃ��Ă��镔���̌����ƒ�����Ԃ��܂�
	bool CheckHit(std::shared_ptr<Collider> other, Vector2& overlapLength);

protected:
	// ���������̊֐��͊O���ɂ͌����Ȃ�
	// �O�������CheckHit(Collider)�Ă�ł�����āA���̒��Ńt���O�g���ĕ��򂷂�
	// �ł�������Ɠ����蔻��̎�ނ������邲�Ƃɂǂ�ǂ�g�ݍ��킹�������Ċ֐����������Ă�������Ȃ�
	// �ł��悭�l������I�[�o�[���[�h��������͓̂����ł���

	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="other">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHitCircle(std::shared_ptr<CircleCollider> other);
	/// <summary>
	/// �����蔻��̎擾(�΋�`)
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual bool CheckHitBox(std::shared_ptr<BoxCollider> other);
};

