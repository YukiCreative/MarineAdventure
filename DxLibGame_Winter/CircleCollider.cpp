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
    const CircleCollider& circle = *this;
    const BoxCollider& box = otherRect;

    CollisionStatus result;
    Vector2 nearestCrossPos;
    bool isCross = false;
    std::vector<float> lineDist;
    std::vector<CollisionStatus> lineColStatus;
    // 現在有効なラインコライダーとの接触判定
    for (int i = 0; i < kLineColNum; ++i)
    {
        if (!box.GetIsLineValid(static_cast<LineDir>(i))) continue;
        // ポリモーフィズム化
        lineColStatus.push_back(circle.CheckHit(*box.GetLineCol()[i], offset));
        result.isCollide |= lineColStatus.back().isCollide; // 今追加したやつ
        // ここで、overlapを取得するために、現在地点から一番近い線分を出したい
        // 現在地点から、それぞれの線分の中心へ向かうベクトルの大きさを比べる
        lineDist.push_back((circle.GetPos() - box.GetLineCol()[i]->SegmentMidPoint()).SqrMagnitude());
    }
    // 一番近い線のoverlapを採用
    auto it = std::min_element(lineDist.begin(), lineDist.end());
    size_t index = std::distance(lineDist.begin(), it);
    if (lineColStatus.size() == 0)
    {
        result.overlap = Vector2::Zero();
    }
    else
    {
        result.overlap = lineColStatus[index].overlap;
    }
    return result;
}

CollisionStatus CircleCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& velocity) const
{
    CollisionStatus result;
    // あえて客観的に自分を操作することで、反対の当たり判定に流用しやすくする
    const CircleCollider& circle = *this;
    const LineCollider& line = otherLine;
    Vector2 futurePos = circle.GetPos() + velocity;

    // 円の移動量ベクトルと、壁線分が交わるかどうかを調べる
    float segmentMinLength = Segment_Segment_MinLength(circle.GetPos(), futurePos, line.GetFirstPos(), line.GetSecondPos());
    bool isCross = (segmentMinLength == 0.0f);

    // 当たっているかは、半径を考慮して出す
    result.isCollide = (segmentMinLength < circle.GetRadius());

    // 円の未来の位置と「直線」の最近傍点を出す
    Vector2 futureNearestPos = geo::GetSegmentIntercept(futurePos, line.GetFirstPos(), line.GetSecondPos());
    // もしこれが線分の端ならめり込まなかったことに
    if (futureNearestPos == line.GetFirstPos() || futureNearestPos == line.GetSecondPos())
    {
        result.overlap = Vector2::Zero();
        return result;
    }

    // 交わっていれば
    if (isCross)
    {
        // 中心を、移動量から、futureNearestPos + 半径分戻したい
        Vector2 closestToNext = futurePos - futureNearestPos;
        // 円の半径の長さの、中心→最近傍点の向きのベクトルを作成
        Vector2 closestToNextN = closestToNext.GetNormalize();
        Vector2 radiusVec = closestToNextN * circle.GetRadius();
        Vector2 overlap = radiusVec + closestToNext;
        result.overlap = overlap;
    }
    else
    {
        // この場合中心を、移動量から半径 - futureNearestPosだけ戻したい
        Vector2 nextToClosest = futureNearestPos - futurePos;
        // 円の半径の長さの、中心→最近傍点の向きのベクトルを作成
        Vector2 nextToClosestN = nextToClosest.GetNormalize();
        Vector2 radiusVec = nextToClosestN * circle.GetRadius();
        Vector2 overlap = radiusVec - nextToClosest;
        result.overlap = overlap;
    }

    return result;
}
