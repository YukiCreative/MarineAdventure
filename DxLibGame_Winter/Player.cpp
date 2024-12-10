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
#include <cassert>

#include "LineCollider.h"

namespace
{
	// �v���C���[�̓����蔻��Ɏg���܂�
	constexpr float kRaduis = 20.0f;
	// Axis���ł�������񂾂�
	constexpr float kMoveForceFactor = 0.0002f;
	constexpr float kDashForceFactor = 0.0003f;
	constexpr float kStrongAttackMoveFactor = 0.0001f;
	constexpr float kAttackFrame = 60.0f;
	constexpr float kInvincibleFrame = 90.0f;
	constexpr float kStrongAttackForce = 20.0f;
}

// �������삳��Ă��Ȃ���ԁB
void Player::Normal(Input& input, Vector2& axis)
{
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger("Attack"))
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
	if (input.IsPressed("Dash"))
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
	if (input.IsTrigger("Attack"))
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
	if (!input.IsPressed("Dash"))
	{
		m_graphic = "M";
		m_physics->UseConstantForce(false);
		m_state = &Player::Move;
		(this->*m_state)(input, axis); // ���̏�Ԃ̓��e�����s
		return;
	}
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger("Attack"))
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
	m_physics->AddForce(axis * kStrongAttackMoveFactor);
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
	m_graphHandle = LoadGraph("Data/Image/Penguin.png");
	assert(m_graphHandle != -1);
}

void Player::Update()
{
	// ���͂Ƃ�
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	// ���݂̏�Ԃ̏���
	(this->*m_state)(input, axis);

	// ������Update�͓��͂Ȃǂŗ͂��Z�o���I�������Ɏ��s���邱�ƁB
	Vector2 vel = m_physics->Update();

	// �����Ń}�b�v�̕ǂƂ̓����蔻��
	auto& collidableMapChips = m_map.lock()->GetCollidableMapChips();
	for (const auto& chip : collidableMapChips)
	{
		for (int i = 0; i < 4; ++i)
		{
			// ������f�o�b�O�\�����Ă�̂Ō�ŏ�������
			Vector2 firstPos = chip->GetCollider().GetLineCol()[i]->GetFirstPos();
			Vector2 secondPos = chip->GetCollider().GetLineCol()[i]->GetSecondPos();
			firstPos = m_camera.Capture(firstPos);
			secondPos = m_camera.Capture(secondPos);
			DrawLine(firstPos.x, firstPos.y, secondPos.x, secondPos.y, 0x00ff00);
			Vector2 midPoint = chip->GetCollider().GetLineCol()[i]->SegmentMidPoint();
			midPoint = m_camera.Capture(midPoint);
			DrawPixel(midPoint.x, midPoint.y, 0xff00ff);
		}

		CollisionStatus col = m_collider->CheckHit(chip->GetCollider(), vel);
		if (!col.isCollide) continue;
		//if (!chip->CanCollide()) continue;

		// �F��ς��Ă݂�
		chip->ChangeGraph_Debug();

		// ����ŏI���ƃX�^�b�N���邵�A�����łȂ��Ă��ǂɋz���t���悤�ȋ����ɂȂ��Ĉ�a��������̂�
		// �͂�������
		Vector2 overlapN = col.overlap.GetNormalize();
		Vector2 addforce(vel.x * std::abs(overlapN.x), vel.y * std::abs(overlapN.y));
		m_physics->AddForce(-addforce * 1.5f);

		vel -= col.overlap;
	}

	// �Ō�Ɉړ�
	m_pos += vel;
}

void Player::Draw() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(kRaduis), 0xff0000);
	DrawRotaGraph(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), 0.1, 0.0, m_graphHandle, true);
	DrawString(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), m_graphic.c_str(), 0x00ff00);
#if _DEBUG
	DrawFormatString(0, 15, 0xffffff, "PlayerPos:x = %f, y = %f", m_pos.x, m_pos.y);
	DrawFormatString(0, 105, 0xffffff, "screenPos:x = %f, y = %f", screenPos.x, screenPos.y);
#endif
}

Vector2 Player::GetVel() const
{
	return m_physics->GetVel();
}

bool Player::CheckState(PlayerState stateID) const
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
