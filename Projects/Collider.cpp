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
	// �����̓����蔻�菈���@�K�v�ɂȂ��������Ă�
	//else if (other.GetKind() == ColKind::kLine)
	//{
	//	LineCollider& line = dynamic_cast<LineCollider&>(other);
	//	return CheckHitLine(line);
	//}

	assert(false && "�񋓂ɑ΂��鏈���Ȃ��Ȃ��H");
	return CollisionStatus();
}

CollisionStatus Collider::CheckHit(Collider& other, const Vector2& offset) const
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
	else if (other.GetKind() == ColKind::kLine)
	{
		LineCollider& line = dynamic_cast<LineCollider&>(other);
		return CheckHitLine(line, offset);
	}

	assert(false && "�񋓂ɑ΂��鏈���Ȃ��Ȃ��H");
	return CollisionStatus();
}