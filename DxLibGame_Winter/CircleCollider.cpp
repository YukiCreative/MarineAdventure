#include "CircleCollider.h"
#include "BoxCollider.h"
#include <algorithm>

CircleCollider::CircleCollider(Vector2& pos, float radius) :
    Collider(ColKind::kCircle, pos),
    m_radius(radius)
{
}

bool CircleCollider::CheckHitCircle(std::shared_ptr<CircleCollider> otherCircle)
{
    // �~�`�Ɖ~�`�̓����蔻��
    // �����Ɠ�̉~�̍��v���a���ׂ�
    float dist = (m_pos - otherCircle->GetPos()).SqrMagnitude();
    float radiusLength = (m_radius + otherCircle->GetRadius()) * (m_radius + otherCircle->GetRadius());

    return dist <= radiusLength;
}

bool CircleCollider::CheckHitBox(std::shared_ptr<BoxCollider> otherRect)
{
    // ��`�̕ӂŁA�~�̒��S���W�ƈ�ԋ߂��_���o��
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(m_pos.x, otherRect->Left(), otherRect->Right());
    nearestPoint.y = std::clamp(m_pos.y, otherRect->Top(), otherRect->Bottom());

    // �o������_�̋������A�~�̔��a�ȉ��Ȃ瓖�����Ă���
    float distance = (m_pos - nearestPoint).SqrMagnitude();
    return distance <= m_radius * m_radius;
}
