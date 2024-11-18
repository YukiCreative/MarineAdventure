#include "BoxCollider.h"
#include "CircleCollider.h"
#include <algorithm>
#include <memory>

BoxCollider::BoxCollider(Vector2& pos, float w, float h) :
	Collider(ColKind::kBox, pos),
	m_rectWidth(w),
	m_rectHeight(h)
{
}

bool BoxCollider::CheckHit(CircleCollider& otherCircle)
{
	Vector2 circlePos = otherCircle.GetPos();
	// 矩形の辺で、円の中心座標と一番近い点を出す
	Vector2 nearestPoint;
	nearestPoint.x = std::clamp(circlePos.x, Left(), Right());
	nearestPoint.y = std::clamp(circlePos.y, Top(), Bottom());

	// 出した二点の距離が、円の半径以下なら当たっている
	float distance = (circlePos - nearestPoint).SqrMagnitude();
	return distance <= otherCircle.GetRadius() * otherCircle.GetRadius();
}

bool BoxCollider::CheckHit(BoxCollider& otherRect)
{
	// 自分の右端より相手の左端のほうが右側なら…を繰り返す
	if (Right() < otherRect.Left()) return false;
	if (Left() > otherRect.Right()) return false;
	if (Top() > otherRect.Bottom()) return false; 
	if (Bottom() < otherRect.Top()) return false;
	// ここまでくれば当たっている
	return true;
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