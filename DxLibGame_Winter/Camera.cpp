#include "Camera.h"

void Camera::Update()
{
	// Move��������
	m_pos += m_velocity;
	// �ړ��ʃ��Z
	m_velocity = Vector2();
	// ���g���Ȃ�������return
	if (m_refObj.expired()) return;

	// �I�u�W�F�N�g���J�����̒��S������l���ꂽ��ǔ�������
	// ���̍ہA������肶����ǔ�����
	// �X�s�[�h�������قǃJ�����̒ǔ����瓦��A��ʒ[�Ɉʒu����
	m_pos = Vector2::Lerp(m_pos, m_refObj.lock()->GetPos(), 0.1f);
}

Vector2 Camera::Capture(const Vector2& objPos) const
{
	Vector2 screenPos = objPos - m_pos;
	// �X�N���[���̒����ɂȂ�悤�ɕ␳
	screenPos.x += Game::kScreenWidth * 0.5f;
	screenPos.y += Game::kScreenHeight * 0.5f;
	return screenPos;
}

void Camera::SetFollowObject(std::weak_ptr<GameObject> obj)
{
	// nullptr�̉\������
	m_refObj = obj;
}
