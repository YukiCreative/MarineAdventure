#include "Camera.h"

void Camera::Update()
{
	// Move分を消費
	m_pos += m_velocity;
	// 移動量リセ
	m_velocity = Vector2();
	// 中身がなかったらreturn
	if (m_refObj.expired()) return;

	// オブジェクトがカメラの中心から一定値離れたら追尾したい
	// その際、ゆっくりじんわり追尾する
	// スピードが早いほどカメラの追尾から逃れ、画面端に位置する
	m_pos = Vector2::Lerp(m_pos, m_refObj.lock()->GetPos(), 0.1f);
}

Vector2 Camera::Capture(const Vector2& objPos) const
{
	Vector2 screenPos = objPos - m_pos;
	// スクリーンの中央になるように補正
	screenPos.x += Game::kScreenWidth * 0.5f;
	screenPos.y += Game::kScreenHeight * 0.5f;
	return screenPos;
}

void Camera::SetFollowObject(std::weak_ptr<GameObject> obj)
{
	// nullptrの可能性あり
	m_refObj = obj;
}
