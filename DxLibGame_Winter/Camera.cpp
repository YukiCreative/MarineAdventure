#include "Camera.h"
#include "MapConstants.h"

namespace
{
	constexpr int kScreenHalfWidth = Game::kScreenWidth / 2;
	constexpr int kScreenHalfHeight = Game::kScreenHeight / 2;
}

void Camera::Update()
{
	// 今回のフレームの移動後の座標
	Vector2 velocity;
	// 追尾する対象があれば
	if (!m_refObj.expired())
	{
		// オブジェクトがカメラの中心から一定値離れたら追尾したい
		// その際、ゆっくりじんわり追尾する
		// スピードが早いほどカメラの追尾から逃れ、画面端に位置する
		velocity = Vector2::LerpValue(m_pos, m_refObj.lock()->GetPos(), 0.1f);
	}
	// Move分を消費
	velocity += m_velocity;
	// 移動量リセ
	m_velocity = Vector2();
	// カメラのposから見えている画面端のX.Yをだして、それがマップの範囲を超えている時、
	// その向きにカメラが移動しなくなる
	// でもカメラにマップの参照を持たせたくない
	if (m_pos.x <= 0)
	{
		if (velocity.x < 0)
		{
			m_pos.x = 0;
			velocity.x = 0;
		}
	}
	if (m_pos.y <= 0)
	{
		if (velocity.y < 0)
		{
			m_pos.y = 0;
			velocity.y = 0;
		}
	}
	// 画面端s
	if (m_pos.x >= MapConstants::kChipSize * (m_mapSize.x - 17))
	{
		if (velocity.x > 0)
		{
			m_pos.x = MapConstants::kChipSize * (m_mapSize.x - 17);
			velocity.x = 0;
		}
	}
	if (m_pos.y >= MapConstants::kChipSize * (m_mapSize.y - 10))
	{
		if (velocity.y > 0)
		{
			m_pos.y = MapConstants::kChipSize * (m_mapSize.y - 10);
			velocity.y = 0;
		}
	}

	// 最後に運動
	m_pos += velocity;

	// drawOffsetを作る
	m_drawOffset.x = m_pos.x - kScreenHalfWidth;
	m_drawOffset.y = m_pos.y - kScreenHalfHeight;
}

Vector2 Camera::Capture(const Vector2& objPos) const
{
	return objPos - m_drawOffset;
}

void Camera::SetFollowObject(std::weak_ptr<GameObject> obj)
{
	m_refObj = obj;
}
