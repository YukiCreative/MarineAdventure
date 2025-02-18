#include "Collider.h"
#include <cassert>
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "LineCollider.h"

Collider::Collider(const ColKind& kind, Vector2& pos) :
	m_pos(pos),
	m_kind(kind),
	m_offset()
{
}

Collider::Collider(const ColKind& kind, Vector2& pos, const Vector2& offset) :
	m_pos(pos),
	m_kind(kind),
	m_offset(offset)
{
}

CollisionStatus Collider::CheckHit(Collider& other) const
{
	// フラグ管理
	if (other.GetKind() == ColKind::kCircle)
	{
		// ここで型変換をすることで
		CircleCollider& circle = dynamic_cast<CircleCollider&>(other);
		// この関数がCircleColliderの関数として呼ばれる
		return CheckHitCircle(circle);
	}
	else if (other.GetKind() == ColKind::kBox)
	{
		BoxCollider& box = dynamic_cast<BoxCollider&>(other);
		return CheckHitBox(box);
	}
	// 線分の当たり判定処理　必要になったら作ってね
	//else if (other.GetKind() == ColKind::kLine)
	//{
	//	LineCollider& line = dynamic_cast<LineCollider&>(other);
	//	return CheckHitLine(line);
	//}

	assert(false && "列挙に対する処理なくない？");
	return CollisionStatus();
}

CollisionStatus Collider::CheckHit(Collider& other, const Vector2& offset) const
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
		return CheckHitBox(box, offset);
	}
	else if (other.GetKind() == ColKind::kLine)
	{
		LineCollider& line = dynamic_cast<LineCollider&>(other);
		return CheckHitLine(line, offset);
	}

	assert(false && "列挙に対する処理なくない？");
	return CollisionStatus();
}