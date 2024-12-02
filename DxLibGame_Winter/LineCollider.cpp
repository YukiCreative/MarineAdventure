#include "LineCollider.h"
#include <cassert>

LineCollider::LineCollider(Vector2& posRef, Vector2 firstPosOffset, const Vector2 secondPosOffset) :
	Collider(ColKind::kLine, posRef),
	m_firstPosOffset(firstPosOffset),
	m_secondPosOffset(secondPosOffset)
{
}

// �́[����������܂��[��
CollisionStatus LineCollider::CheckHitCircle(const CircleCollider& otherCircle) const
{
	assert(false && "���߂��@�����ł��ĂȂ���");
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const
{
	assert(false && "���߂��@�����ł��ĂȂ���");
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitBox(const BoxCollider& otherRect) const
{
	assert(false && "���߂��@�����ł��ĂȂ���");
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const
{
	assert(false && "���߂��@�����ł��ĂȂ���");
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& offset, Vector2& crossPos) const
{
	assert(false && "���߂��@�����ł��ĂȂ���");
	return CollisionStatus();
}
