#include "Collider.h"
#include <cassert>
#include "CircleCollider.h"
#include "BoxCollider.h"
#include <typeinfo>
#include "CollisionStatus.h"

Collider::Collider(ColKind kind, Vector2& pos) :
	m_pos(pos),
	m_posOffset(),
	m_kind(kind)
{
}

CollisionStatus Collider::CheckHit(Collider& other)
{
	// フラグ管理
	if (other.GetKind() == ColKind::kCircle)
	{
		// ここで型変換をすることで
		auto circle = dynamic_cast<CircleCollider&>(other);
		// この関数がCircleColliderの関数として呼ばれる
		return CheckHitCircle(circle);
	}
	else if (other.GetKind() == ColKind::kBox)
	{
		auto box = dynamic_cast<BoxCollider&>(other);
		return CheckHitBox(box);
	}

	assert(false && "列挙に対する処理なくない？");
	return CollisionStatus();
}

CollisionStatus Collider::CheckHit(Collider& other, const Vector2& offset)
{
	// フラグ管理
	if (other.GetKind() == ColKind::kCircle)
	{
		// ここで型変換をすることで
		auto circle = dynamic_cast<CircleCollider&>(other);
		// この関数がCircleColliderの関数として呼ばれる
		return CheckHitCircle(circle, offset);
	}
	else if (other.GetKind() == ColKind::kBox)
	{
		auto box = dynamic_cast<BoxCollider&>(other);
		return CheckHitBox(box);
	}

	assert(false && "列挙に対する処理なくない？");
	return CollisionStatus();
}