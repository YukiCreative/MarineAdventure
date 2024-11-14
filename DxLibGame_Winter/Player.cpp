#include "Player.h"
#include <DxLib.h>
#include "Input.h"
#include "Physics.h"
#include "game.h"
#include "MapSystem.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "MapChip.h"
#include "Camera.h"

namespace
{
	// ���e�X�g
	int kRaduis = 20;
}

Player::Player() :
	m_physics(std::make_shared<Physics>(1.0f, 1.0f))
{
	m_collider = std::make_shared<CircleCollider>(m_pos, kRaduis);
}

void Player::Update(std::shared_ptr<MapSystem> map)
{
	// ���͂��Ƃ��āA�����B
	Input& input = Input::GetInstance();

	Vector2 axis = input.GetInputAxis();

	// A�{�^���Ń_�b�V����Ԃ�(����̓A�^�b�N�Ɠ����ɂł��Ȃ��悤��)
	if (input.IsPressed(PAD_INPUT_1))
	{
		axis *= 1.5f;
	}
	// ��
	m_physics->AddForce(axis * 0.01f);
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger(PAD_INPUT_2))
	{
		m_physics->Stop();
		m_physics->AddForce(axis);
	}

	// �����蔻��̏���
	// �}�b�v�`�b�v���Ɣ��肷��
	for (auto& chip : map->GetMapCihps())
	{
		if (m_collider->CheckHit(chip->GetCollider()))
		{
			// �}�b�v�`�b�v�̎�ނ����������
			// �}�b�v�`�b�v�Ɠ������Ă�����A�����̑O��̑��x�̌����ɉ�����
		}
	}

	// ������Update�͓��͂Ȃǂŗ͂��Z�o���I�������Ɏ��s���邱�ƁB
	// �������Z+�ړ�
	m_pos += m_physics->Update();
}

void Player::Draw(std::shared_ptr<Camera> camera) const
{
	Vector2 screenPos = camera->Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), kRaduis, 0xff0000);
#if _DEBUG
	DrawFormatString(0, 15, 0x000000, "PlayerPos:x = %f, y = %f", m_pos.x, m_pos.y);
	DrawFormatString(0, 105, 0x000000, "screenPos:x = %f, y = %f", screenPos.x, screenPos.y);
#endif
}

Vector2 Player::GetVel() const
{
	return m_physics->GetVel();
}
