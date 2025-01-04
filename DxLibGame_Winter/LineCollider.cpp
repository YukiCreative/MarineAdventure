#include "LineCollider.h"
#include <cassert>

LineCollider::LineCollider(Vector2& posRef, const Vector2& firstPosOffset, const Vector2& secondPosOffset) :
	Collider(ColKind::kLine, posRef),
	m_firstPosOffset(firstPosOffset),
	m_secondPosOffset(secondPosOffset)
{
}

LineCollider::LineCollider(Vector2& posRef, const Vector2& firstPosOffset, const Vector2& secondPosOffset, const Vector2& offset) :
	Collider(ColKind::kLine, posRef, offset),
	m_firstPosOffset(firstPosOffset),
	m_secondPosOffset(secondPosOffset)
{
}

void LineCollider::DrawColliderRange_Debug(const Vector2& cameraOffset) const
{
	Vector2 firstDrawPos = GetFirstPos() - cameraOffset;
	Vector2 secondDrawPos = GetSecondPos() - cameraOffset;
	DrawLine(static_cast<int>(firstDrawPos.x), static_cast<int>(firstDrawPos.y), static_cast<int>(secondDrawPos.x), static_cast<int>(secondDrawPos.y), 0xff0000);
}

CollisionStatus LineCollider::CheckHitCircle(const CircleCollider& otherCircle) const
{
	assert(false && "ごめんよ　実装できてないんだ");
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const
{
	assert(false && "ごめんよ　実装できてないんだ");
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitBox(const BoxCollider& otherRect) const
{
	assert(false && "ごめんよ　実装できてないんだ");
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const
{
	assert(false && "ごめんよ　実装できてないんだ");
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& offset) const
{
	assert(false && "ごめんよ　実装できてないんだ");
	return CollisionStatus();
}
