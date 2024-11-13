#include "Player.h"
#include <DxLib.h>
#include "Input.h"
#include "Physics.h"
#include "game.h"
#include "MapSystem.h"
#include "CircleCollider.h"
#include "MapChip.h"

namespace
{
	// ���e�X�g
	int kRaduis = 20;

	constexpr float kInitPosX = Game::kScreenWidth * 0.5f;
	constexpr float kInitPosY = Game::kScreenHeight * 0.5f;
}

Player::Player() :
	m_physics(std::make_shared<Physics>(1.0f, 1.0f)),
	m_pos(kInitPosX, kInitPosY)
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
		if (m_collider->CheckHit(chip->Collider()))
		{
			// ����͉��ŁA���private�ɖ߂�
			chip->SetGraph();
		}
	}

	// ������Update�͓��͂Ȃǂŗ͂��Z�o���I�������Ɏ��s���邱�ƁB

	// �����̓}�b�v������ȏ�X�N���[�����Ȃ����ǂ����𔻒肵�Ď������ړ����邩�ǂ����ς�����
	m_physics->Update();
	//if (�X�N���[���ł��Ȃ�)
	//{
	//	m_pos += m_physics->GetVel();
	//}
}

void Player::Draw()
{
	DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), kRaduis, 0xff0000);
#if _DEBUG
	DrawFormatString(0, 15, 0x000000, "PlayerPos:x = %f, y = %f", m_pos.x, m_pos.y);
#endif
}

Vector2 Player::GetVel()
{
	return m_physics->GetVel();
}
