#include "Camera.h"

void Camera::Update()
{
	// Move分を消費
	m_pos += m_velocity;
	// 移動量リセ
	m_velocity = Vector2();
	// 追尾する対象があれば
	if (!m_refObj.expired())
	{
		// オブジェクトがカメラの中心から一定値離れたら追尾したい
		// その際、ゆっくりじんわり追尾する
		// スピードが早いほどカメラの追尾から逃れ、画面端に位置する
		m_pos = Vector2::Lerp(m_pos, m_refObj.lock()->GetPos(), 0.1f);
	}
	// drawOffsetを作る
	m_drawOffset.x = m_pos.x - Game::kScreenWidth * 0.5f;
	m_drawOffset.y = m_pos.y - Game::kScreenHeight * 0.5f;
}

Vector2 Camera::Capture(const Vector2& objPos) const
{
	return objPos - m_drawOffset;
}

void Camera::SetFollowObject(std::weak_ptr<GameObject> obj)
{
	// nullptrの可能性あり
	m_refObj = obj;
}
