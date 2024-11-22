#include "CircleCollider.h"
#include "BoxCollider.h"
#include <algorithm>
#include <cmath>
#include "Calculation.h"

CircleCollider::CircleCollider(Vector2& pos, float radius) :
    Collider(ColKind::kCircle, pos),
    m_radius(radius)
{
}

CollisionStatus CircleCollider::CheckHitCircle(CircleCollider& otherCircle) const 
{
    // 円形と円形の当たり判定
    // 距離と二つの円の合計半径を比べる
    Vector2 distVec = m_pos - otherCircle.GetPos();
    float dist = distVec.SqrMagnitude();
    float radiusLength = m_radius + otherCircle.GetRadius();
    Vector2 distUnit = distVec.GetNormalize();
    Vector2 radiusVec =  distUnit * radiusLength;

    CollisionStatus result;
    result.isCollide = dist <= radiusLength * radiusLength;
    result.overlap = radiusVec - distVec;

    return result;
}

CollisionStatus CircleCollider::CheckHitCircle(CircleCollider& otherCircle, const Vector2& offset) const
{
    // 自分の位置を補正込みで考える あとは一緒
    Vector2 distVec = m_pos - otherCircle.GetPos() + offset;
    float dist = distVec.SqrMagnitude();
    float radiusLength = m_radius + otherCircle.GetRadius();
    Vector2 distUnit = distVec.GetNormalize();
    Vector2 radiusVec = distUnit * radiusLength;

    CollisionStatus result;
    result.isCollide = dist <= radiusLength;
    result.overlap = radiusVec - distVec;

    return result;
}

CollisionStatus CircleCollider::CheckHitBox(BoxCollider& otherRect) const
{
    // 矩形の辺で、円の中心座標と一番近い点を出す
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(m_pos.x, otherRect.Left(), otherRect.Right());
    nearestPoint.y = std::clamp(m_pos.y, otherRect.Top(), otherRect.Bottom());
    
    // 出した二点の距離が、円の半径以下なら当たっている
    Vector2 distVec = m_pos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // 円の半径の大きさをした、distVecの向きのベクトルを作りたい
    Vector2 radiusVec = distVec.GetNormalize() * m_radius;

    CollisionStatus result;
    result.isCollide = sqrDist <= m_radius * m_radius;
    result.overlap = radiusVec - distVec;

    return result;
}

CollisionStatus CircleCollider::CheckHitBox(BoxCollider& otherRect, const Vector2& offset) const
{
    // 補正
    Vector2 correctedPos = m_pos + offset;
    // 矩形の辺で、円の中心座標と一番近い点を出す
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(correctedPos.x, otherRect.Left(), otherRect.Right());
    nearestPoint.y = std::clamp(correctedPos.y, otherRect.Top(), otherRect.Bottom());

    // 出した二点の距離が、円の半径以下なら当たっている
    Vector2 distVec = correctedPos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // 円の半径の大きさをした、distVecの向きのベクトルを作りたい
    Vector2 radiusVec = distVec.GetNormalize() * m_radius;

    CollisionStatus result;
    result.isCollide = sqrDist <= m_radius * m_radius;
    result.overlap = radiusVec - distVec;

    return result;
}
