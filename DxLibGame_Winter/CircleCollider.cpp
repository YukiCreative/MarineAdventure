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
    result.normal = -distUnit;

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
    result.normal = -distUnit;

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
    // 自分らの中心同士をつなげたベクトルがどんな向きかで判定
    // これ上下逆になるよね
    Vector2 pointDist = m_pos - otherRect.GetPos();
    float distDeg = std::atan2(pointDist.y, pointDist.x) * Calculation::kRadToDeg;
    // 範囲を0~360にさせていただく
    if (distDeg < 0) distDeg += 360;
    // 四角形の中心から右上の頂点に向かうベクトルの角度
    // これを元にほかの3方向を出す
    Vector2 rectVec = Vector2(otherRect.Right(), otherRect.Bottom()) - otherRect.GetPos();
    float rectDeg = std::atan2(rectVec.y, rectVec.x) * Calculation::kRadToDeg;
    if (distDeg > rectDeg && distDeg <= 180 - rectDeg) result.normal = Vector2::Down();
    if (distDeg > 180 - rectDeg && distDeg <= 180 + rectDeg) result.normal = Vector2::Left();
    if (distDeg > 180 + rectDeg && distDeg <= 360 - rectDeg) result.normal = Vector2::Up();
    if (distDeg > 360 - rectDeg || distDeg <= rectDeg) result.normal = Vector2::Right();

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
    // 自分らの中心同士をつなげたベクトルがどんな向きかで判定
    // これ上下逆になるよね
    Vector2 pointDist = correctedPos - otherRect.GetPos();
    float distDeg = std::atan2(pointDist.x, pointDist.y) * Calculation::kRadToDeg;
    // 範囲を0~360にさせていただく
    if (distDeg < 0) distDeg += 360;
    // 四角形の中心から右上の頂点に向かうベクトルの角度
    // これを元にほかの3方向を出す
    Vector2 rectVec = Vector2(otherRect.Right(), otherRect.Bottom()) - otherRect.GetPos();
    float rectDeg = std::atan2(5, 1) * Calculation::kRadToDeg;
    printf("rectVec: x=%f,Y=%f\n", rectVec.x, rectVec.y);
    printf("distDeg=%f\n", distDeg);
    printf("rectDeg=%f\n", rectDeg);
    if (distDeg > rectDeg && distDeg <= 180 - rectDeg) result.normal = Vector2::Down();
    if (distDeg > 180 - rectDeg && distDeg <= 180 + rectDeg) result.normal = Vector2::Left();
    if (distDeg > 180 + rectDeg && distDeg <= 360 - rectDeg) result.normal = Vector2::Up();
    if (distDeg > 360 - rectDeg || distDeg <= rectDeg) result.normal = Vector2::Right();

    return result;
}
