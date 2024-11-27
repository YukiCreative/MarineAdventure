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

bool CircleCollider::CheckHitCircle(CircleCollider& otherCircle) const 
{
    // 円形と円形の当たり判定
    // 距離と二つの円の合計半径を比べる
    Vector2 distVec = m_pos - otherCircle.GetPos();
    float dist = distVec.SqrMagnitude();
    float radiusLength = m_radius + otherCircle.GetRadius();
    return dist <= radiusLength * radiusLength;
}

bool CircleCollider::CheckHitCircle(CircleCollider& otherCircle, const Vector2& offset) const
{
    // 自分の位置を補正込みで考える あとは一緒
    Vector2 distVec = m_pos - otherCircle.GetPos() + offset;
    float dist = distVec.SqrMagnitude();
    float radiusLength = m_radius + otherCircle.GetRadius();

    return dist <= radiusLength * radiusLength;
}

bool CircleCollider::CheckHitBox(BoxCollider& otherRect) const
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

    return sqrDist <= m_radius * m_radius;
}

bool CircleCollider::CheckHitBox(BoxCollider& otherRect, const Vector2& offset) const
{   
    // 自分がBoxでもここだけ変えれば大丈夫
    CircleCollider circle = *this;
    BoxCollider box = otherRect;
    // 円の補正
    Vector2 futurePos = circle.GetPos() + offset;
    // 四角形の各頂点をベクトル化
    Vector2 rVertexTopRight(box.Right(), box.Top());
    Vector2 rVertexTopLeft(box.Left(), box.Top());
    Vector2 rVertexBottomRight(box.Right(), box.Bottom());
    Vector2 rVertexBottomLeft(box.Left(), box.Bottom());
    // 移動ベクトルが、四角形の辺に当たっているかチェック
    bool isHit = !Segment_Segment_MinLength(circle.GetPos(), futurePos, rVertexTopLeft, rVertexBottomLeft);
    isHit &= !Segment_Segment_MinLength(circle.GetPos(), futurePos, rVertexBottomLeft, rVertexBottomRight);
    isHit &= !Segment_Segment_MinLength(circle.GetPos(), futurePos, rVertexTopLeft, rVertexTopRight);
    isHit &= !Segment_Segment_MinLength(circle.GetPos(), futurePos, rVertexBottomRight, rVertexTopRight);

    return isHit;
}
