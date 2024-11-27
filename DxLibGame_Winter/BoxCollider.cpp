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

bool BoxCollider::CheckHitCircle(CircleCollider& otherCircle) const
{
    Vector2 circlePos = otherCircle.GetPos();
    // 矩形の辺で、円の中心座標と一番近い点を出す
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(circlePos.x, Left(), Right());
    nearestPoint.y = std::clamp(circlePos.y, Top(), Bottom());

    // 出した二点の距離が、円の半径以下なら当たっている
    Vector2 distVec = circlePos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // 円の半径の大きさをした、distVecの向きのベクトルを作りたい
    Vector2 radiusVec = distVec.GetNormalize() * otherCircle.GetRadius();

    return sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
}

bool BoxCollider::CheckHitCircle(CircleCollider& otherCircle, const Vector2& offset) const
{
    // めんどくさいから円の方動かしてるってことでいい？
    Vector2 circlePos = otherCircle.GetPos() - offset;
    // 矩形の辺で、円の中心座標と一番近い点を出す
    Vector2 nearestPoint;
    nearestPoint.x = std::clamp(circlePos.x, Left(), Right());
    nearestPoint.y = std::clamp(circlePos.y, Top(), Bottom());

    // 出した二点の距離が、円の半径以下なら当たっている
    Vector2 distVec = circlePos - nearestPoint;
    float sqrDist = distVec.SqrMagnitude();
    // 円の半径の大きさをした、distVecの向きのベクトルを作りたい
    Vector2 radiusVec = distVec.GetNormalize() * otherCircle.GetRadius();

    return sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
}

bool BoxCollider::CheckHitBox(BoxCollider& otherRect) const 
{
    // 自分の右端より相手の左端のほうが右側なら…を繰り返す
    return  Right() < otherRect.Left() &&
            Left() > otherRect.Right() &&
            Top() > otherRect.Bottom() &&
            Bottom() < otherRect.Top();
}

bool BoxCollider::CheckHitBox(BoxCollider& otherRect, const Vector2& offset) const
{
    // 自分の右端より相手の左端のほうが右側なら…を繰り返す
    return  Right() + offset.x < otherRect.Left() &&
            Left() + offset.x > otherRect.Right() &&
            Top() + offset.y > otherRect.Bottom() &&
            Bottom() + offset.y < otherRect.Top();
}

float BoxCollider::Right() const
{
	return m_pos.x + m_rectWidth * 0.5f;
}

float BoxCollider::Left() const
{
	return m_pos.x - m_rectWidth * 0.5f;
}

float BoxCollider::Top() const
{
	return m_pos.y - m_rectHeight * 0.5f;
}

float BoxCollider::Bottom() const 
{
	return m_pos.y + m_rectHeight * 0.5f;
}