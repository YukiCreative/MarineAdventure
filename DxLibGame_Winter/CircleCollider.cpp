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
    // 円形と円形の当たり判定
    // 距離と二つの円の合計半径を比べる
    float dist = (m_pos - otherCircle->GetPos()).SqrMagnitude();
    float radiusLength = (m_radius + otherCircle->GetRadius()) * (m_radius + otherCircle->GetRadius());

    return dist <= radiusLength;
}

bool CircleCollider::CheckHitBox(std::shared_ptr<BoxCollider> otherRect)
{
    // 矩形の辺で、円の中心座標と一番近い点を出す
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(m_pos.x, otherRect->Left(), otherRect->Right());
    nearestPoint.y = std::clamp(m_pos.y, otherRect->Top(), otherRect->Bottom());

    // 出した二点の距離が、円の半径以下なら当たっている
    float distance = (m_pos - nearestPoint).SqrMagnitude();
    return distance <= m_radius * m_radius;
}
