#include "Camera.h"
#include <algorithm>
#include "MapConstants.h"

void Camera::Tracking()
{
	// �ǔ�����Ώۂ������
	if (m_refObj.expired()) return;

	Vector2 targetPos = m_refObj.lock()->GetPos();
	// �I�u�W�F�N�g���J�����̒��S������l���ꂽ��ǔ�������
	// ���̍ہA�������`�悷��
	m_velocity = Vector2::LerpValue(m_pos, targetPos, m_lerpStrength);
}

void Camera::Limiting()
{
	// �J������pos���猩���Ă����ʒ[��X.Y�������āA���ꂪ�}�b�v�͈̔͂𒴂��Ă��鎞�A
	// ���̌����ɃJ�������ړ����Ȃ��Ȃ�
	// �ł��J�����Ƀ}�b�v�̎Q�Ƃ������������Ȃ�
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
}