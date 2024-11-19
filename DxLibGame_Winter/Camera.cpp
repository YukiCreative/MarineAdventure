#include "Camera.h"

void Camera::Update()
{
	// Move��������
	m_pos += m_velocity;
	// �ړ��ʃ��Z
	m_velocity = Vector2();
	// �ǔ�����Ώۂ������
	if (!m_refObj.expired())
	{
		// �I�u�W�F�N�g���J�����̒��S������l���ꂽ��ǔ�������
		// ���̍ہA������肶����ǔ�����
		// �X�s�[�h�������قǃJ�����̒ǔ����瓦��A��ʒ[�Ɉʒu����
		m_pos = Vector2::Lerp(m_pos, m_refObj.lock()->GetPos(), 0.1f);
	}
	// drawOffset�����
	m_drawOffset.x = m_pos.x - Game::kScreenWidth * 0.5f;
	m_drawOffset.y = m_pos.y - Game::kScreenHeight * 0.5f;
}

Vector2 Camera::Capture(const Vector2& objPos) const
{
	return objPos - m_drawOffset;
}

void Camera::SetFollowObject(std::weak_ptr<GameObject> obj)
{
	// nullptr�̉\������
	m_refObj = obj;
}
