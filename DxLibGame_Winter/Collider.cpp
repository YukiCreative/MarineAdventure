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

bool Collider::CheckHit(Collider& other)
{
	return other.CheckHit(*this);
}

bool Collider::CheckHit(Collider& other, Vector2& overlapLength)
{
	// �V�˂ł�
	return other.CheckHit(*this);
}

bool Collider::CheckHit(CircleCollider& other)
{
	assert(false && "��������Ă��Ȃ��֐��ł�");
	return false;
}

bool Collider::CheckHit(BoxCollider& other)
{
	assert(false && "��������Ă��Ȃ��֐��ł�");
	return false;
}