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
	// �t���O�Ǘ�
	if (other.GetKind() == ColKind::kCircle)
	{
		// �����Ō^�ϊ������邱�Ƃ�
		auto circle = dynamic_cast<CircleCollider&>(other);
		// ���̊֐���CircleCollider�̊֐��Ƃ��ČĂ΂��
		return CheckHitCircle(circle);
	}
	else if (other.GetKind() == ColKind::kBox)
	{
		auto box = dynamic_cast<BoxCollider&>(other);
		return CheckHitBox(box);
	}

	assert(false && "�񋓂ɑ΂��鏈���Ȃ��Ȃ��H");
	return CollisionStatus();
}

CollisionStatus Collider::CheckHit(Collider& other, const Vector2& offset)
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
		return CheckHitBox(box);
	}

	assert(false && "�񋓂ɑ΂��鏈���Ȃ��Ȃ��H");
	return CollisionStatus();
}