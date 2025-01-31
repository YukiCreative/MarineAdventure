#include "Camera.h"
#include <algorithm>
#include "MapConstants.h"

void Camera::Tracking()
{
	// 追尾する対象があれば
	if (m_refObj.expired()) return;

	Vector2 targetPos = m_refObj.lock()->GetPos();
	// オブジェクトがカメラの中心から一定値離れたら追尾したい
	// その際、少し先を描画する
	m_velocity = Vector2::LerpValue(m_pos, targetPos, m_lerpStrength);
}

void Camera::Limiting()
{
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
	// 画面端
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
}

Camera::Camera() :
	m_lerpStrength(0.1f)
{
}

Camera::Camera(Vector2 initPos) :
	m_pos(initPos),
	m_lerpStrength(0.1f)
{
}

void Camera::Update()
{
	// 移動量リセ
	m_velocity = Vector2::Zero();

	// もしMoveされてたらMove分を消費
	// そしてオブジェクトへの追尾をしない
	if (m_moveAmount.SqrMagnitude() != 0)
	{
		m_velocity += m_moveAmount;
		m_moveAmount = Vector2::Zero();
	}
	else
	{
		Tracking();
		Limiting();
	}

	// 最後に運動
	m_pos += m_velocity;

	// drawOffsetを作る
	m_drawOffset.x = m_pos.x - Game::kScreenHalfWidth;
	m_drawOffset.y = m_pos.y - Game::kScreenHalfHeight;
}

Vector2 Camera::Capture(const Vector2& objPos) const
{
	return objPos - m_drawOffset;
}

void Camera::FitMap()
{
	Move(Vector2(1, 1));
}