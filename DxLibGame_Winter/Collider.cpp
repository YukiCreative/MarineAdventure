#include "Collider.h"
#include <cassert>
#include "CircleCollider.h"
#include "BoxCollider.h"

Collider::Collider(ColKind kind, Vector2& pos) :
	m_pos(pos),
	m_posOffset(),
	m_kind(kind)
{
}

bool Collider::CheckHit(std::shared_ptr<Collider> other)
{
	if (other->GetKind() == ColKind::kCircle)
	{
		// ‚±‚±‚ÅŒ^•ÏŠ·‚ğ‚·‚é‚±‚Æ‚Å
		auto circle = std::dynamic_pointer_cast<CircleCollider>(other);
		// ‚±‚ÌŠÖ”‚ªCircleCollider‚ÌŠÖ”‚Æ‚µ‚ÄŒÄ‚Î‚ê‚é
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
	assert(false && "À‘•‚³‚ê‚Ä‚¢‚È‚¢ŠÖ”‚Å‚·");
	return false;
}

bool Collider::CheckHitBox(std::shared_ptr<BoxCollider> other)
{
	assert(false && "À‘•‚³‚ê‚Ä‚¢‚È‚¢ŠÖ”‚Å‚·");
	return false;
}