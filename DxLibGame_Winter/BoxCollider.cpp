#include "BoxCollider.h"
#include "CircleCollider.h"

BoxCollider::BoxCollider(Vector2& pos, float h, float v) :
	Collider(pos),
	m_rectHorizontalLength(h),
	m_rectVerticalLength(v)
{
}

bool BoxCollider::CheckHit(CircleCollider& other)
{
	return false;
}

bool BoxCollider::CheckHit(BoxCollider& other)
{
	// 自分の右端より相手の左端のほうが右側なら…を繰り返す
	if (Right() < other.Left()) return false;
	if (Left() > other.Right()) return false;
	if (Top() > other.Bottom()) return false; 
	if (Bottom() < other.Top()) return false;
	// ここまでくれば当たっている
	return true;
}

float BoxCollider::Right()
{
	return m_pos.x + m_rectHorizontalLength * 0.5f;
}

float BoxCollider::Left()
{
	return m_pos.x - m_rectHorizontalLength * 0.5f;
}

float BoxCollider::Top()
{
	return m_pos.y - m_rectVerticalLength * 0.5f;
}

float BoxCollider::Bottom()
{
	return m_pos.y + m_rectVerticalLength * 0.5f;
}