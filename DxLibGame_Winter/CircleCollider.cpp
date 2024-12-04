#include "CircleCollider.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include <algorithm>
#include <cmath>
#include "Calculation.h"
#include <DxLib.h>
#include "Geometry.h"
#include <vector>
#include <cassert>
#include <typeinfo>

namespace
{
    constexpr int kLineColNum = 4;
}

CircleCollider::CircleCollider(Vector2& pos, float radius) :
    Collider(ColKind::kCircle, pos),
    m_radius(radius)
{
}

CollisionStatus CircleCollider::CheckHitCircle(const CircleCollider& otherCircle) const 
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

CollisionStatus CircleCollider::CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const
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

CollisionStatus CircleCollider::CheckHitBox(const BoxCollider& otherRect) const
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

CollisionStatus CircleCollider::CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const
{
    // 線分四つとの当たり判定
    const CircleCollider& circle = *this;
    const BoxCollider& box = otherRect;

    // CollisionStatusと交点をまとめる
    using LineColStatus = std::pair<CollisionStatus, Vector2>;
    std::array<LineColStatus, kLineColNum> lineColStatus{};
    bool isHit = false;
    for (int i = 0; i < kLineColNum; ++i)
    {
        // ポリモーフィズム化したい
        lineColStatus[i].first = circle.CheckHitLine(*box.GetLineCol()[0], offset, lineColStatus[i].second);
        // 判定は一つでも当たっていたらOK
        isHit |= lineColStatus[i].first.isCollide;
    }

    CollisionStatus result;
    result.isCollide = isHit;
    // 当たった線分で、交点が最も現在位置に近い線分のめり込みを採用する
    // どれも交わっていないときは、当たった線分は一つだけ　のはずなのでそれを使う
    if (isHit)
    {
        LineColStatus nearestLine = lineColStatus[0];
        for (int i = 1; i < kLineColNum; ++i)
        {
            // ※NaVの大きさは-1
            // と思ったが適用されてなさそう
            // 安全にダウンキャストしたい
            if (nearestLine.second.SqrMagnitude() < lineColStatus[i].second.SqrMagnitude())
            {
                nearestLine = lineColStatus[i];
            }
        }
        result.overlap = nearestLine.first.overlap;
    }
    else
    {
        result.overlap = Vector2::Zero();
    }
    return result;
}

CollisionStatus CircleCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& velocity, Vector2& crossPos) const
{
    CollisionStatus result;
    // あえて客観的に自分を操作することで、反対の当たり判定に流用しやすくする
    const CircleCollider& circle = *this;
    const LineCollider& line = otherLine;

    // 円の移動量ベクトルと、壁線分が交わるかどうかを調べる
    float segmentMinLength = Segment_Segment_MinLength(circle.GetPos(), velocity, line.GetFirstPos(), line.GetSecondPos());
    bool isCross = segmentMinLength == 0.0f;

    Vector2 futurePos = circle.GetPos() + velocity;
    // 円の未来の位置と線分の最近傍点を出す
    Vector2 futureNearestPos = geo::GetIntercept(circle.GetPos(), line.GetFirstPos(), line.GetSecondPos());

    // 中心を、移動量から、futureNearestPos + 半径分戻したい
    Vector2 overlapTemp = futureNearestPos - futurePos;
    // 円の半径の長さの、中心→最近傍点の向きのベクトルを作成
    Vector2 radiusVec = overlapTemp.GetNormalize() * circle.GetRadius();
    overlapTemp += radiusVec;

    // 交わっていれば
    if (isCross)
    {
        result.overlap = overlapTemp;
        // 交点を返してあげる
        crossPos = futureNearestPos;
    }
    else
    {
        // 反対
        result.overlap = -overlapTemp;
        // 交わらなかった
        crossPos = NaV();
    }

    // 当たっているかは、半径を考慮して出す
    result.isCollide = segmentMinLength <= circle.GetRadius();
    return result;
}
