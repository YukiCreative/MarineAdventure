#include "CircleCollider.h"
#include "BoxCollider.h"

CircleCollider::CircleCollider(Vector2 pos, float radius) :
    Collider(pos),
    m_radius(radius)
{
}

bool CircleCollider::CheckHit(CircleCollider& other)
{
    // �~�`�Ɖ~�`�̓����蔻��
    // �����Ɠ�̉~�̍��v���a���ׂ�
    float dist = (m_pos - other.GetPos()).SqrMagnitude();
    float radiusLength = (m_radius + other.GetRadius()) * (m_radius + other.GetRadius());
    if (dist <= radiusLength)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CircleCollider::CheckHit(BoxCollider& other)
{
    return false;
}
