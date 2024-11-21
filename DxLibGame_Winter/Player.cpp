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
	// �v���C���[�̓����蔻��Ɏg���܂�
	constexpr float kRaduis = 20.0f;
	// Axis���ł�������񂾂�
	constexpr float kMoveForceFactor = 0.0002f;
	constexpr float kDashForceFactor = 0.0003f;
	constexpr float kStrongAttackForceFactor = 0.0001f;
	constexpr int kAttackFrame = 60;
	constexpr int kInvincibleFrame = 90;
	constexpr int kStrongAttackForce = 20;
}

// �������삳��Ă��Ȃ���ԁB
void Player::Normal(Input& input, Vector2& axis)
{
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger(PAD_INPUT_2))
	{
		m_graphic = "A";
		m_physics->UseConstantForce(false);
		m_state = &Player::Attack;
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// �X�e�B�b�N��Move��
	if (axis.SqrMagnitude() > 10000)
	{
		m_graphic = "M";
		m_physics->UseConstantForce(false);
		m_state = &Player::Move;
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// ���݂̈ړ������ɂ���ă��[�V������ς���
}

// �ړ����Ă܂�
void Player::Move(Input& input, Vector2& axis)
{
	// �_�b�V��������Ă���Dash��
	if (input.IsPressed(PAD_INPUT_1))
	{
		m_graphic = "D";
		m_physics->UseConstantForce(false);
		m_state = &Player::Dash;
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// ���͂��Ȃ�������Nomal��
	if (axis.SqrMagnitude() < 10000)
	{
		SetStateNormal();
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger(PAD_INPUT_2))
	{
		m_graphic = "SA";
		m_physics->UseConstantForce(false);
		// �����ŗ͂�������
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		m_state = &Player::StrongAttack;
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// ��
	m_physics->AddForce(axis * kMoveForceFactor);
	// ���݂̈ړ������ɂ���ă��[�V������ς���
}

// �����ł��B
void Player::Dash(Input& input, Vector2& axis)
{
	// �_�b�V��������ĂȂ�������Move��
	if (!input.IsPressed(PAD_INPUT_1))
	{
		m_graphic = "M";
		m_physics->UseConstantForce(false);
		m_state = &Player::Move;
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger(PAD_INPUT_2))
	{
		m_graphic = "SA";
		m_physics->UseConstantForce(false);
		// �����ŗ͂�������
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		m_state = &Player::StrongAttack;
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// 	// ���͂��Ȃ�������Nomal��
	if (axis.SqrMagnitude() < 10000)
	{
		SetStateNormal();
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// ��
	m_physics->AddForce(axis * kDashForceFactor);
	// ���[�V�������ς��̂͂����������
}

void Player::Attack(Input& input, Vector2& axis)
{
	// �U�����������
	// ��莞�Ԍo������Normal��
	++m_stateFrameCount;
	if (m_stateFrameCount >= kAttackFrame)
	{
		SetStateNormal();
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// �ړ����ł���
	m_physics->AddForce(axis * kMoveForceFactor);
}

void Player::StrongAttack(Input& input, Vector2& axis)
{
	// ��莞�Ԍo������Normal��
	++m_stateFrameCount;
	if (m_stateFrameCount >= kAttackFrame)
	{
		SetStateNormal();
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// �U�����������
	// ������ƈړ����ł���
	m_physics->AddForce(axis * kStrongAttackForceFactor);
}

void Player::Damage(Input& input, Vector2& axis)
{
	// �_���[�W���󂯂��炱�̏�Ԃ�
	// ��莞�Ԗ��G
	++m_stateFrameCount;
	if (m_stateFrameCount >= kInvincibleFrame)
	{
		SetStateNormal();
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
}

void Player::Death(Input& input, Vector2& axis)
{
	// ���S���[�V����
	// �ʂ̃V�[����
}

void Player::SetStateNormal()
{
	// ��ԑJ�ڂ��鏈�����d�����Ă����̂�
	m_stateFrameCount = 0;
	m_graphic = "N";
	m_physics->UseConstantForce(true);
	m_state = &Player::Normal;
}

Player::Player(Camera& camera, Vector2 spawnPos) :
	GameObject(spawnPos),
	m_physics(std::make_shared<Physics>(1.0f, 1.0f)),
	m_state(&Player::Normal),
	m_graphic("N"),
	m_stateFrameCount(0),
	m_hp(0),
	m_camera(camera)
{
	m_collider = std::make_shared<CircleCollider>(m_pos, kRaduis);
}

void Player::Update(MapSystem& map)
{
	// ���͂Ƃ�
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	// ���݂̏�Ԃ̏���
	(this->*m_state)(input, axis);

	// ������Update�͓��͂Ȃǂŗ͂��Z�o���I�������Ɏ��s���邱�ƁB
	Vector2 vel = m_physics->Update();

	// �����蔻��̏���
	// �}�b�v�`�b�v���Ɣ��肷��
	for (auto& chip : map.GetMapCihps())
	{
		if (m_collider->CheckHit(chip->GetCollider()))
		{
			// �ړ�������̈ʒu���ǂƐڐG���Ă����瓖�������ʂɂ���Ĉړ��ʂ��C��

		}
	}

	// �Ō�Ɉړ�
	m_pos += vel;
}

void Player::Draw() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(kRaduis), 0xff0000);
	DrawString(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), m_graphic.c_str(), 0x000000);
#if _DEBUG
	DrawFormatString(0, 15, 0x000000, "PlayerPos:x = %f, y = %f", m_pos.x, m_pos.y);
	DrawFormatString(0, 105, 0x000000, "screenPos:x = %f, y = %f", screenPos.x, screenPos.y);
#endif
}

Vector2 Player::GetVel() const
{
	return m_physics->GetVel();
}

bool Player::CheckState(PlayerState stateID)
{
	// �񋓑̂�switch����o�ł������@���[
	switch (stateID)
	{
	case PlayerState::kNormal:
		return m_state == &Player::Normal;
		break;
	case PlayerState::kMove:
		return m_state == &Player::Move;
		break;
	case PlayerState::kDash:
		return m_state == &Player::Dash;
		break;
	case PlayerState::kAttack:
		return m_state == &Player::Attack;
		break;
	case PlayerState::kStrongAttack:
		return m_state == &Player::StrongAttack;
		break;
	case PlayerState::kDamage:
		return m_state == &Player::Damage;
		break;
	case PlayerState::kDeath:
		return m_state == &Player::Death;
		break;
	default:
		return false;
		break;
	}
}
