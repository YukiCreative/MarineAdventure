#include "Camera.h"
#include "MapConstants.h"

namespace
{
	constexpr int kScreenHalfWidth = Game::kScreenWidth / 2;
	constexpr int kScreenHalfHeight = Game::kScreenHeight / 2;
}

void Camera::Update()
{
	// ����̃t���[���̈ړ���̍��W
	Vector2 velocity;
	// �ǔ�����Ώۂ������
	if (!m_refObj.expired())
	{
		// �I�u�W�F�N�g���J�����̒��S������l���ꂽ��ǔ�������
		// ���̍ہA������肶����ǔ�����
		// �X�s�[�h�������قǃJ�����̒ǔ����瓦��A��ʒ[�Ɉʒu����
		velocity = Vector2::LerpValue(m_pos, m_refObj.lock()->GetPos(), 0.1f);
	}
	// Move��������
	velocity += m_velocity;
	// �ړ��ʃ��Z
	m_velocity = Vector2();
	// �J������pos���猩���Ă����ʒ[��X.Y�������āA���ꂪ�}�b�v�͈̔͂𒴂��Ă��鎞�A
	// ���̌����ɃJ�������ړ����Ȃ��Ȃ�
	// �ł��J�����Ƀ}�b�v�̎Q�Ƃ������������Ȃ�
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
	// ��ʒ[s
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

	// �Ō�ɉ^��
	m_pos += velocity;

	// drawOffset�����
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
