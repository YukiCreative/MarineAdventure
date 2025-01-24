#include "BoxCollider.h"
#include "CircleCollider.h"
#include <algorithm>
#include <memory>
#include "Calculation.h"
#include "LineCollider.h"
#include <cassert>
#include <vector>

namespace
{
    constexpr int kLineColInBox = 4;
}

BoxCollider::BoxCollider(Vector2& pos, const float& w, const float& h) :
	Collider(ColKind::kBox, pos),
	m_rectWidth(w),
	m_rectHeight(h)
{
    // 中心からの相対距離を出してます
    Vector2 topLeft =  Vector2(Left(), Top()) - GetPos();
    Vector2 bottomLeft =  Vector2(Left(), Bottom()) - GetPos();
    Vector2 topRight = Vector2(Right(), Top()) - GetPos();
    Vector2 bottomRight = Vector2(Right(), Bottom()) - GetPos();
    // 各辺をCollider化
    //constexpr int offset = 10;
    //m_lines[static_cast<int>(LineDir::Top)] = std::make_shared<LineCollider>(m_pos, topLeft + Vector2(offset, 0), topRight + Vector2(-offset, 0)); // 上
    //m_lines[static_cast<int>(LineDir::Left)] = std::make_shared<LineCollider>(m_pos, topLeft + Vector2(0, offset), bottomLeft + Vector2(0, -offset)); // 左
    //m_lines[static_cast<int>(LineDir::Right)] = std::make_shared<LineCollider>(m_pos, bottomRight + Vector2(0, -offset), topRight + Vector2(0, offset)); // 右
    //m_lines[static_cast<int>(LineDir::Bottom)] = std::make_shared<LineCollider>(m_pos, bottomLeft + Vector2(offset, 0), bottomRight + Vector2(-offset, 0)); // 下
    // それぞれの線分が始点⇒終点⇒始点でつながるように作る
    m_lines[static_cast<int>(LineDir::Top)]    = std::make_shared<LineCollider>(m_pos, topLeft,     topRight   ); // 上
    m_lines[static_cast<int>(LineDir::Right)]  = std::make_shared<LineCollider>(m_pos, topRight,    bottomRight); // 右
    m_lines[static_cast<int>(LineDir::Bottom)] = std::make_shared<LineCollider>(m_pos, bottomRight, bottomLeft ); // 下
    m_lines[static_cast<int>(LineDir::Left)]   = std::make_shared<LineCollider>(m_pos, bottomLeft,  topLeft    ); // 左
    
    for (auto& isValid : m_validLineCol)
    {
        isValid = true;
    }
}

// offset付ける以外変わらないかな
BoxCollider::BoxCollider(Vector2& pos, const float& w, const float& h, const Vector2& offset) :
    Collider(ColKind::kBox, pos, offset),
    m_rectWidth(w),
    m_rectHeight(h)
{
    Vector2 topLeft = Vector2(Left(), Top()) - GetPos();
    Vector2 bottomLeft = Vector2(Left(), Bottom()) - GetPos();
    Vector2 topRight = Vector2(Right(), Top()) - GetPos();
    Vector2 bottomRight = Vector2(Right(), Bottom()) - GetPos();
    // m_posが入っていますが正常です
    // それぞれの線分が始点⇒終点⇒始点でつながるように作る
    m_lines[static_cast<int>(LineDir::Top)]    = std::make_shared<LineCollider>(m_pos, topLeft,     topRight,    offset); // 上
    m_lines[static_cast<int>(LineDir::Right)]  = std::make_shared<LineCollider>(m_pos, topRight,    bottomRight, offset); // 右
    m_lines[static_cast<int>(LineDir::Left)]   = std::make_shared<LineCollider>(m_pos, bottomLeft,  topLeft,     offset); // 左
    m_lines[static_cast<int>(LineDir::Bottom)] = std::make_shared<LineCollider>(m_pos, bottomRight, bottomLeft,  offset); // 下

    for (auto& isValid : m_validLineCol)
    {
        isValid = true;
    }
}

void BoxCollider::DrawColliderRange_Debug(const Vector2& cameraOffset) const
{
    // 四角の当たり判定を書く
    //DrawBox(static_cast<int>(Left() - cameraOffset.x), static_cast<int>(Top() - cameraOffset.y), static_cast<int>(Right() - cameraOffset.x), static_cast<int>(Bottom() - cameraOffset.y), 0xff0000, false);

    // ↑
    // これら二つは同じ結果を描画することが確認できている
    // ↓
    
     //線分の描画を四回やる
    for (const auto& line : m_lines)
    {
        line->DrawColliderRange_Debug(cameraOffset);
    }
}

CollisionStatus BoxCollider::CheckHitCircle(const CircleCollider& otherCircle) const
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

    CollisionStatus result;
    result.isCollide = sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
    result.overlap = radiusVec - distVec;

    return result;
}

CollisionStatus BoxCollider::CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const
{
    //// めんどくさいから円の方動かしてるってことでいい？
    //Vector2 circlePos = otherCircle.GetPos() - offset;
    //// 矩形の辺で、円の中心座標と一番近い点を出す
    //Vector2 nearestPoint;
    //nearestPoint.x = std::clamp(circlePos.x, Left(), Right());
    //nearestPoint.y = std::clamp(circlePos.y, Top(), Bottom());

    //// 出した二点の距離が、円の半径以下なら当たっている
    //Vector2 distVec = circlePos - nearestPoint;
    //float sqrDist = distVec.SqrMagnitude();
    //// 円の半径の大きさをした、distVecの向きのベクトルを作りたい
    //Vector2 radiusVec = distVec.GetNormalize() * otherCircle.GetRadius();

    //CollisionStatus result;
    //result.isCollide = sqrDist <= otherCircle.GetRadius() * otherCircle.GetRadius();
    //result.overlap = radiusVec - distVec;

    //return result;

    const CircleCollider& circle = otherCircle;
    const BoxCollider& box = *this;

    CollisionStatus result;
    Vector2 nearestCrossPos;
    bool isCross = false;
    std::vector<float> lineDist;
    std::vector<CollisionStatus> lineColStatus;
    // 現在有効なラインコライダーとの接触判定
    for (int i = 0; i < kLineColInBox; ++i)
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

CollisionStatus BoxCollider::CheckHitLine(const LineCollider& otherLine, const Vector2& offset) const
{
    assert(false && "ごめんよ　実装できてないんだ");
    return CollisionStatus();
}