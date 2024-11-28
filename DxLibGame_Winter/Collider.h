#pragma once
#include "Vector2.h"
#include <memory>

class CircleCollider;
class BoxCollider;
class LineCollider;

enum class ColKind
{
	kCircle,
	kBox,
	kLine,
};

/// <summary>
/// �R���C�_�[���v�Z������ɏo�Ă��邢���ȏ����ЂƂ܂Ƃ߂ɂ��ĕԂ���������
/// </summary>
struct CollisionStatus
{
	// �������Ă��邩
	bool isCollide = false;
	// ���������ʂɐ����ɁA�ǂꂭ�炢�̌����A�傫���ł߂荞��ł��邩���o���Ă���܂�
	Vector2 overlap = Vector2::Zero();
};

/// <summary>
/// �����蔻��������ǂ���N���X
/// </summary>
class Collider
{
protected:
	/// <summary>
	/// �������A�^�b�`����Ă���I�u�W�F�N�g�̍��W���Q��
	/// </summary>
	Vector2& m_pos;

	const ColKind m_kind;

public:
	Collider(ColKind kind, Vector2& pos);

	Vector2 GetPos() const { return m_pos; }
	// �g���Ȃ�
	Vector2* GetPVec() const { return &m_pos; }
	ColKind GetKind() const { return m_kind; }

	CollisionStatus CheckHit(Collider& other) const;
	// �␳���� ���ꂩ����Z����ړ��ʂ���������Ƃ��ȂǂɗL��
	CollisionStatus CheckHit(Collider& other, const Vector2& offset) const;

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
	virtual CollisionStatus CheckHitCircle(const CircleCollider& other) const = 0;
	virtual CollisionStatus CheckHitCircle(const CircleCollider& other, const Vector2& offset) const = 0;
	/// <summary>
	/// �����蔻��̎擾(�΋�`)
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	virtual CollisionStatus CheckHitBox(const BoxCollider& other) const = 0;
	virtual CollisionStatus CheckHitBox(const BoxCollider& other, const Vector2& offset) const = 0;
	// ���ꂵ���������
	virtual CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& offset) const = 0;
};

