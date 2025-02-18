#include "Camera.h"
#include <algorithm>
#include "MapConstants.h"
#include "game.h"

namespace
{
	constexpr float kLerpMax = 1.0f;
	constexpr float kLerpMin = 0.1f;
}

void Camera::Tracking()
{
	// �ǔ�����Ώۂ������
	if (m_refObj.expired()) return;

	Vector2 targetPos = m_refObj.lock()->GetPos();
	// �I�u�W�F�N�g��lerp�ł�����ǔ�����
	// �J�������瓦��Ȃ��悤�ɂ��������ɒǔ�����
	Vector2 rerativeVec = m_pos - targetPos;
	const float klerpThreshold = Game::kScreenHalfHeight * 0.5f;
	if (rerativeVec.SqrMagnitude() > klerpThreshold * klerpThreshold)
	{
		m_lerpStrength += 0.01f;
	}
	else
	{
		m_lerpStrength -= 0.01f;
	}
	// �璷����
	m_lerpStrength = std::clamp(m_lerpStrength, kLerpMin, kLerpMax);
	m_velocity = Vector2::LerpValue(m_pos, targetPos, m_lerpStrength);
}

void Camera::Limiting()
{
	// �J������pos���猩���Ă����ʒ[��X.Y�������āA���ꂪ�}�b�v�͈̔͂𒴂��Ă��鎞�A
	// ���̌����ɃJ�������ړ����Ȃ��Ȃ�
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
	// ��ʒ[
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
	// �ړ��ʃ��Z
	m_velocity = Vector2::Zero();

	// ����Move����Ă���Move��������
	// �����ăI�u�W�F�N�g�ւ̒ǔ������Ȃ�
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

	// �Ō�ɉ^��
	m_pos += m_velocity;

	// drawOffset�����
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
	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
		m_velocity.x = 0;
	}
	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		m_velocity.y = 0;
	}
	// ��ʒ[
	if (m_pos.x >= MapConstants::kChipSize * (m_mapSize.x - MapConstants::kWidthChipNum))
	{
		m_pos.x = MapConstants::kChipSize * (m_mapSize.x - MapConstants::kWidthChipNum);
		m_velocity.x = 0;
	}
	if (m_pos.y >= MapConstants::kChipSize * (m_mapSize.y - MapConstants::kHeightChipNum))
	{
		m_pos.y = MapConstants::kChipSize * (m_mapSize.y - MapConstants::kHeightChipNum);
		m_velocity.y = 0;
	}
}