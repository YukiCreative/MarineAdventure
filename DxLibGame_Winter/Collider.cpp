#include "Collider.h"
#include <cassert>
#include "CircleCollider.h"
#include "BoxCollider.h"
#include <typeinfo>

Collider::Collider(ColKind kind, Vector2& pos) :
	m_pos(pos),
	m_posOffset(),
	m_kind(kind)
{
}

bool Collider::CheckHit(std::shared_ptr<Collider> other)
{
	// ���ǃt���O�Ǘ��Ȃ̎c�O�߂���
	if (other->GetKind() == ColKind::kCircle)
	{
		// �����Ō^�ϊ������邱�Ƃ�
		auto circle = std::dynamic_pointer_cast<CircleCollider>(other);
		// ���̊֐���CircleCollider�̊֐��Ƃ��ČĂ΂��
		return CheckHitCircle(circle);
	}
	else if (other->GetKind() == ColKind::kBox)
	{
		auto box = std::dynamic_pointer_cast<BoxCollider>(other);
		return CheckHitBox(box);
	}
}

bool Collider::CheckHit(std::shared_ptr<Collider> other, Vector2& overlapLength)
{
	if (other->GetKind() == ColKind::kCircle)
	{
		// �����Ō^�ϊ������邱�Ƃ�
		auto circle = std::dynamic_pointer_cast<CircleCollider>(other);
		// ���̊֐���CircleCollider�̊֐��Ƃ��ČĂ΂��
		return CheckHitCircle(circle);
	}
	else if (other->GetKind() == ColKind::kBox)
	{
		auto box = std::dynamic_pointer_cast<BoxCollider>(other);
		return CheckHitBox(box);
	}
}

bool Collider::CheckHitCircle(std::shared_ptr<CircleCollider> other)
{
	assert(false && "��������Ă��Ȃ��֐��ł�");
	return false;
}

bool Collider::CheckHitBox(std::shared_ptr<BoxCollider> other)
{
	assert(false && "��������Ă��Ȃ��֐��ł�");
	return false;
}