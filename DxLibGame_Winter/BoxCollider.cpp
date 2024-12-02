#include "BoxCollider.h"
#include "CircleCollider.h"
#include <algorithm>
#include <memory>
#include "Calculation.h"
#include "LineCollider.h"
#include <cassert>

BoxCollider::BoxCollider(Vector2& pos, float w, float h) :
	Collider(ColKind::kBox, pos),
	m_rectWidth(w),
	m_rectHeight(h)
{
    // 中心からの相対距離を出してます
    Vector2 topLeft = m_pos - Vector2(Left(), Top());
    Vector2 bottomLeft = m_pos = Vector2(Left(), Bottom());
    Vector2 topRight = m_pos = Vector2(Right(), Top());
    Vector2 bottomRight = m_pos - Vector2(Right(), Bottom());
    // 各辺をCollider化
    m_lines[0] = std::make_shared<LineCollider>(m_pos, topLeft, topRight);
    m_lines[1] = std::make_shared<LineCollider>(m_pos, topLeft, bottomLeft);
    m_lines[2] = std::make_shared<LineCollider>(m_pos, topRight, bottomRight);
    m_lines[3] = std::make_shared<LineCollider>(m_pos, bottomLeft, bottomRight);
}

CollisionStatus BoxCollider::CheckHitCircle(const CircleCollider& otherCircle) const
{
    CollisionStatus result;
    assert(false && "ごめんよ　実装できてないんだ");
    return result;
}

CollisionStatus BoxCollider::CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const
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

    CollisionStatus result;
    result.isCollide = sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
    result.overlap = radiusVec - distVec;

    return result;
}

CollisionStatus BoxCollider::CheckHitBox(const BoxCollider& otherRect) const 
{
    CollisionStatus result;
	// 自分の右端より相手の左端のほうが右側なら…を繰り返す
    result.isCollide = 
        Right() < otherRect.Left() &&
        Left() > otherRect.Right() &&
        Top() > otherRect.Bottom() &&
        Bottom() < otherRect.Top();
    // めり込み無理じゃね
    result.overlap = Vector2::Zero();

    return result;
}

CollisionStatus BoxCollider::CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const
{
    CollisionStatus result;
    // 自分の右端より相手の左端のほうが右側なら…を繰り返す
    result.isCollide =
        Right() + offset.x < otherRect.Left() &&
        Left() + offset.x > otherRect.Right() &&
        Top() + offset.y > otherRect.Bottom() &&
        Bottom() + offset.y < otherRect.Top();
    // めり込み無理じゃね
    result.overlap = Vector2::Zero();

    return result;
}

CollisionStatus BoxCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& offset, Vector2& crossPos) const
{
    assert(false && "ごめんよ　実装できてないんだ");
    return CollisionStatus();
}