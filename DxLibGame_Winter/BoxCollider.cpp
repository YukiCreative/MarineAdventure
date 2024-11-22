#include "BoxCollider.h"
#include "CircleCollider.h"
#include <algorithm>
#include <memory>
#include "Calculation.h"

BoxCollider::BoxCollider(Vector2& pos, float w, float h) :
	Collider(ColKind::kBox, pos),
	m_rectWidth(w),
	m_rectHeight(h)
{
}

CollisionStatus BoxCollider::CheckHitCircle(CircleCollider& otherCircle)
{
    // 矩形の辺で、円の中心座標と一番近い点を出す
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(m_pos.x, Left(), Right());
    nearestPoint.y = std::clamp(m_pos.y, Top(), Bottom());

    // 出した二点の距離が、円の半径以下なら当たっている
    Vector2 distVec = m_pos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // 円の半径の大きさをした、distVecの向きのベクトルを作りたい
    Vector2 radiusVec = distVec.GetNormalize() * otherCircle.GetRadius();

    CollisionStatus result;
    result.isCollide = sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
    result.overlap = radiusVec - distVec;
    // 自分らの中心同士をつなげたベクトルがどんな向きかで判定
    Vector2 pointDist = otherCircle.GetPos() - m_pos;
    float distDeg = std::atan2(pointDist.x, pointDist.y) * Calculation::kRadToDeg;
    // 範囲を0~360にさせていただく
    if (distDeg < 0) distDeg += 360;
    // 四角形の中心から右上の頂点に向かうベクトルの角度
    // これを元にほかの3方向を出す
    Vector2 rectVec = Vector2(Right(), Bottom()) - m_pos;
    float rectDeg = std::atan2(rectVec.x, rectVec.y) * Calculation::kRadToDeg;
    if (distDeg > rectDeg && distDeg <= 180 - rectDeg) result.normal = Vector2::Down();
    if (distDeg > 180 - rectDeg && distDeg <= 180 + rectDeg) result.normal = Vector2::Left();
    if (distDeg > 180 + rectDeg && distDeg <= 360 - rectDeg) result.normal = Vector2::Up();
    if (distDeg > 360 - rectDeg || distDeg <= rectDeg) result.normal = Vector2::Right();

    return result;
}

CollisionStatus BoxCollider::CheckHitCircle(CircleCollider& otherCircle, Vector2 offset)
{
	return CollisionStatus();
}

CollisionStatus BoxCollider::CheckHitBox(BoxCollider& otherRect)
{
    CollisionStatus result;
	// 自分の右端より相手の左端のほうが右側なら…を繰り返す
    result.isCollide = 
        Right() < otherRect.Left() &&
        Left() > otherRect.Right() &&
        Top() > otherRect.Bottom() &&
        Bottom() < otherRect.Top();
    // めり込みと法線出すの無理じゃね
    result.overlap = Vector2::Zero();
    result.normal = Vector2::Zero();

    return result;
}

CollisionStatus BoxCollider::CheckHitBox(BoxCollider& otherRect, Vector2 offset)
{
	return CollisionStatus();
}

float BoxCollider::Right()
{
	return m_pos.x + m_rectWidth * 0.5f;
}

float BoxCollider::Left()
{
	return m_pos.x - m_rectWidth * 0.5f;
}

float BoxCollider::Top()
{
	return m_pos.y - m_rectHeight * 0.5f;
}

float BoxCollider::Bottom()
{
	return m_pos.y + m_rectHeight * 0.5f;
}