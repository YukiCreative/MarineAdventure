#include "LineCollider.h"

CollisionStatus LineCollider::CheckHitCircle(const CircleCollider& otherCircle) const
{
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const
{
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitBox(const BoxCollider& otherRect) const
{
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const
{
	return CollisionStatus();
}

CollisionStatus LineCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& offset, Vector2& crossPos) const
{
	return CollisionStatus();
}
