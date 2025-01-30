#include "Camera.h"
#include "MapConstants.h"

namespace
{
	constexpr int kScreenHalfWidth = Game::kScreenWidth / 2;
	constexpr int kScreenHalfHeight = Game::kScreenHeight / 2;
}

void Camera::Update()
{
	// 移動量リセ
	m_velocity = Vector2::Zero();
	// 追尾する対象があれば
	if (!m_refObj.expired())
	{
		// オブジェクトがカメラの中心から一定値離れたら追尾したい
		// その際、ゆっくりじんわり追尾する
		// スピードが早いほどカメラの追尾から逃れ、画面端に位置する
		m_velocity = Vector2::LerpValue(m_pos, m_refObj.lock()->GetPos(), 0.1f);
	}
	// カメラのposから見えている画面端のX.Yをだして、それがマップの範囲を超えている時、
	// その向きにカメラが移動しなくなる
	// でもカメラにマップの参照を持たせたくない
	if (m_pos.x <= 0)
	{
		if (m_velocity.x < 0)
		{
			m_pos.x = 0;
			m_velocity.x = 0;
		}
	}
	if (m_pos.y <= 0)
	{
		if (m_velocity.y < 0)
		{
			m_pos.y = 0;
			m_velocity.y = 0;
		}
	}
	// 画面端s
	if (m_pos.x >= MapConstants::kChipSize * (m_mapSize.x - MapConstants::kWidthChipNum))
	{
		if (m_velocity.x > 0)
		{
			m_pos.x = MapConstants::kChipSize * (m_mapSize.x - MapConstants::kWidthChipNum);
			m_velocity.x = 0;
		}
	}
	if (m_pos.y >= MapConstants::kChipSize * (m_mapSize.y - MapConstants::kHeightChipNum))
	{
		if (m_velocity.y > 0)
		{
			m_pos.y = MapConstants::kChipSize * (m_mapSize.y - MapConstants::kHeightChipNum);
			m_velocity.y = 0;
		}
	}

	// Move分を消費
	m_velocity += m_moveAmount;
	m_moveAmount = Vector2::Zero();

	// 最後に運動
	m_pos += m_velocity;

	// drawOffsetを作る
	m_drawOffset.x = m_pos.x - kScreenHalfWidth;
	m_drawOffset.y = m_pos.y - kScreenHalfHeight;
}

Vector2 Camera::Capture(const Vector2& objPos) const
{
	return objPos - m_drawOffset;
}

void Camera::FitMap()
{
	Move(Vector2(1, 1));
}
