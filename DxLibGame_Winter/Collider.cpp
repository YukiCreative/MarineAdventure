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
	// Œ‹‹Çƒtƒ‰ƒOŠÇ—‚È‚Ìc”O‰ß‚¬‚é
	if (other.GetKind() == ColKind::kCircle)
	{
		// ‚±‚±‚ÅŒ^•ÏŠ·‚ğ‚·‚é‚±‚Æ‚Å
		auto circle = dynamic_cast<CircleCollider&>(other);
		// ‚±‚ÌŠÖ”‚ªCircleCollider‚ÌŠÖ”‚Æ‚µ‚ÄŒÄ‚Î‚ê‚é
		return CheckHitCircle(circle);
	}
	else if (other.GetKind() == ColKind::kBox)
	{
		auto box = dynamic_cast<BoxCollider&>(other);
		return CheckHitBox(box);
	}

	return false;
}

bool Collider::CheckHit(Collider& other, Vector2& overlapLength)
{
	if (other.GetKind() == ColKind::kCircle)
	{
		// ‚±‚±‚ÅŒ^•ÏŠ·‚ğ‚·‚é‚±‚Æ‚Å
		auto circle = dynamic_cast<CircleCollider&>(other);
		// ‚±‚ÌŠÖ”‚ªCircleCollider‚ÌŠÖ”‚Æ‚µ‚ÄŒÄ‚Î‚ê‚é
		return CheckHitCircle(circle);
	}
	else if (other.GetKind() == ColKind::kBox)
	{
		auto box = dynamic_cast<BoxCollider&>(other);
		return CheckHitBox(box);
	}

	return false;
}

bool Collider::CheckHitCircle(CircleCollider& other)
{
	assert(false && "À‘•‚³‚ê‚Ä‚¢‚È‚¢ŠÖ”‚Å‚·");
	return false;
}

bool Collider::CheckHitBox(BoxCollider& other)
{
	assert(false && "À‘•‚³‚ê‚Ä‚¢‚È‚¢ŠÖ”‚Å‚·");
	return false;
}