#pragma once
#include "Vector2.h"
#include <memory>
#include "CollisionStatus.h"

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

	CollisionStatus CheckHit(Collider& other);
	// �␳���� ���ꂩ����Z����ړ��ʂ���������Ƃ��ȂǂɗL��
	CollisionStatus CheckHit(Collider& other, const Vector2& offset);

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
	virtual CollisionStatus CheckHitCircle(CircleCollider& other) = 0;
	virtual CollisionStatus CheckHitCircle(CircleCollider& other, Vector2 offset) = 0;
	/// <summary>
	/// �����蔻��̎擾(�΋�`)
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual CollisionStatus CheckHitBox(BoxCollider& other) = 0;
	virtual CollisionStatus CheckHitBox(BoxCollider& other, Vector2 offset) = 0;
};

