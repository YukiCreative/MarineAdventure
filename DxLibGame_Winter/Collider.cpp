#include "Collider.h"
#include <cassert>
#include "CircleCollider.h"
#include "BoxCollider.h"

Collider::Collider(ColKind kind, Vector2& pos) :
	m_pos(pos),
	m_kind(kind)
{
}

bool Collider::CheckHit(Collider& other) const
{
	// �t���O�Ǘ�
	if (other.GetKind() == ColKind::kCircle)
	{
		// �����Ō^�ϊ������邱�Ƃ�
		CircleCollider& circle = dynamic_cast<CircleCollider&>(other);
		// ���̊֐���CircleCollider�̊֐��Ƃ��ČĂ΂��
		return CheckHitCircle(circle);
	}
	else if (other.GetKind() == ColKind::kBox)
	{
		BoxCollider& box = dynamic_cast<BoxCollider&>(other);
		return CheckHitBox(box);
	}

	assert(false && "�񋓂ɑ΂��鏈���Ȃ��Ȃ��H");
	return false;
}

bool Collider::CheckHit(Collider& other, const Vector2& offset) const
{
	// �t���O�Ǘ�
	if (other.GetKind() == ColKind::kCircle)
	{
		// �����Ō^�ϊ������邱�Ƃ�
		auto circle = dynamic_cast<CircleCollider&>(other);
		// ���̊֐���CircleCollider�̊֐��Ƃ��ČĂ΂��
		return CheckHitCircle(circle, offset);
	}
	else if (other.GetKind() == ColKind::kBox)
	{
		auto box = dynamic_cast<BoxCollider&>(other);
		return CheckHitBox(box, offset);
	}

	assert(false && "�񋓂ɑ΂��鏈���Ȃ��Ȃ��H");
	return false;
}