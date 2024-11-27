#include "CircleCollider.h"
#include "BoxCollider.h"
#include <algorithm>
#include <cmath>
#include "Calculation.h"
#include <DxLib.h>

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
    // 円の中心が完全にめり込んでいたら、離す方向に行きたい
    
    
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
    Vector2 futurePos = m_pos + offset;
    // 矩形の四隅を変数にしておく
    float rLeft = otherRect.Left();
    float rRight = otherRect.Right();
    float rTop = otherRect.Top();
    float rBottom = otherRect.Bottom();
    // 矩形の辺で、今の円の中心座標と一番近い点を出す(現段階で、めり込んでいないことを願う)
    Vector2 nowNearestPoint;
    nowNearestPoint.x = std::clamp(m_pos.x, rLeft, rRight);
    nowNearestPoint.y = std::clamp(m_pos.y, rTop, rBottom);
    Vector2 futureNearestPoint;
    futureNearestPoint.x = std::clamp(futurePos.x, rLeft, rRight);
    futureNearestPoint.y = std::clamp(futurePos.y, rTop, rBottom);

    // 出した移動後のと最近傍点の距離が、円の半径以下なら当たっている
    Vector2 distVec = futurePos - futureNearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // 移動前の最近傍点から移動後の中心へ伸ばしたベクトル
    Vector2 overlapVec = nowNearestPoint - futurePos;
    // この向きに円の半径の分を足す
    overlapVec += overlapVec.GetNormalize() * m_radius;

    CollisionStatus result;
    result.isCollide = sqrDist <= m_radius * m_radius;
    result.overlap = overlapVec;

    return result;
}
