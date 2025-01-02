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
#include "SceneController.h"
#include "Animation.h"
#include "ImageStore.h"

namespace
{
	// �v���C���[�̓����蔻��Ɏg���܂�
	constexpr float kRaduis = 20.0f;
	constexpr int kMaxHp = 5;
	// Axis���ł�������񂾂�
	constexpr float kMoveForceFactor = 0.0002f;
	constexpr float kDashForceFactor = 0.0003f;
	constexpr float kStrongAttackMoveFactor = 0.0001f;
	constexpr float kAttackFrame = 60.0f;
	constexpr float kInvincibleFrame = 90.0f;
	constexpr float kAttackedRigidFrame = 30.0f;
	constexpr float kStrongAttackForce = 20.0f;
	constexpr float kBounceFactor = 1.2f;
	constexpr int kMoveThreshold = 10000;
	const Vector2 kJumpForce(0.0f, -10.0f);
	const Vector2Int kPlayerGraphSize(32, 32);

	const std::string kIdleAnimPath = "Idle (32x32).png";
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
	if (axis.SqrMagnitude() > kMoveThreshold)
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
	if (axis.SqrMagnitude() < kMoveThreshold)
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
	if (axis.SqrMagnitude() < kMoveThreshold)
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
	// �����������Ă��邩�ǂ������V�[�������t���[���`�F�b�N
	m_isDeleted = true;
}

void Player::Attacked(Input& input, Vector2& axis)
{
	// �d���Ȃ̂Ń��[�V�����ȊO�������Ȃ�
	++m_stateFrameCount;
	if (m_stateFrameCount >= kAttackedRigidFrame)
	{
		SetStateNormal();
		(this->*m_state)(input, axis);
		return;
	}
}

void Player::GNormal(Input& input, Vector2& axis)
{
	// ���낢��ȃ��[�V�����ɂȂ���
	if (input.IsPressed("Jump"))
	{
		m_physics->AddForce(kJumpForce);
		m_state = &Player::Jump;
		(this->*m_state)(input, axis);
		return;
	}
}

void Player::GMove(Input& input, Vector2& axis)
{
	if (input.IsTrigger("Jump"))
	{
		m_physics->AddForce(kJumpForce);
		m_graphic = "Jump";
		m_state = &Player::Jump;
		(this->*m_state)(input, axis);
		return;
	}
	if (axis.SqrMagnitude() < kMoveThreshold)
	{
		m_graphic = "GN";
		m_state = &Player::GNormal;
		(this->*m_state)(input, axis);
		return;
	}
}

void Player::GDash(Input& input, Vector2& axis)
{
	// ������ł�����H�y���M������
}

void Player::Jump(Input& input, Vector2& axis)
{
	// �󒆃��[�V����
	// ���E�ɓ�����
	Vector2 sideAxis = Vector2(axis.x, 0.0f);
	m_physics->AddForce(sideAxis * kMoveForceFactor);
	// �W�����v�̑J�ڂ͑��݂��Ȃ��̂ŁA���i�W�����v���Ȃ�
	// ���n������GNormal��
	// �����͖ԗ��ł��Ă���
}

void Player::SetStateNormal()
{
	// ��ԑJ�ڂ��鏈�����d�����Ă����̂�
	m_stateFrameCount = 0;
	m_graphic = "N";
	m_physics->UseConstantForce(true);
	m_state = &Player::Normal;
}

bool Player::CheckEnvironmentChanged()
{
	// ������񓖂��蔻�肷��
	// ���ׂẴ}�b�v�`�b�v���Ώ�
	const auto& allMapChips = m_map.lock()->GetAllMapChips();
	std::list<MapConstants::Environment> hitEnvironments;
	for (const auto& chip : allMapChips)
	{
		// �ړ��Ȃ������蔻��
		// �����y��
		CollisionStatus col = m_collider->CheckHit(chip->GetCollider());
		if (!col.isCollide) continue;

		// Environment���L��
		hitEnvironments.push_back(chip->GetMapChipData().environment);
	}
	// �����̕�����Ԃ�����Ȃ�������true
	bool result = true;
	for (const auto& env : hitEnvironments)
	{
		result &= !m_physics->CheckState(env);
	}
	return result;
}

void Player::CollideToMapChips()
{
	// �}�b�v�Ƃ̏Փˏ����𕪂���
	// �����Ń}�b�v�̕ǂƂ̓����蔻��
	m_contactAngles.clear();
	auto& collidableMapChips = m_map.lock()->GetCollidableMapChips();
	Vector2 pushBackVec = Vector2::Zero();
	for (const auto& chip : collidableMapChips)
	{
		CollisionStatus col = m_collider->CheckHit(chip->GetCollider(), m_velocity);
		if (!col.isCollide) continue;

		// �F��ς��Ă݂�
		//chip->ChangeGraph_Debug();

		// �ǂɋz���t���悤�ȋ����ɂȂ��Ĉ�a��������̂ŗ͂�������
		Vector2 overlapN = col.overlap.GetNormalize();
		// ���݂̑��x�̕��A�������Ă���ǂ̌��������͂�������
		Vector2 addforce(m_velocity.x * std::abs(overlapN.x), m_velocity.y * std::abs(overlapN.y));
		m_physics->AddForce(-addforce * kBounceFactor);

		// �ڐG�����ʂ̊p�x���擾
		//m_contactAngles.push_back();

		m_velocity -= col.overlap;
	}
}

Player::Player(Camera& camera, Vector2 spawnPos) :
	GameObject(spawnPos),
	m_state(&Player::Normal),
	m_graphic("N"),
	m_stateFrameCount(0),
	m_hp(kMaxHp),
	m_camera(camera)
{
	ImageStore& imageStore = ImageStore::GetInstance();
	m_physics = std::make_shared<Physics>(1.0f, 1.0f),
		m_collider = std::make_shared<CircleCollider>(m_pos, kRaduis);
	// ��������A�j���[�V�����̏�����
	m_idleAnim = std::make_shared<Animation>();
	m_idleAnim->Init(kIdleAnimPath, kPlayerGraphSize, 2);
	m_nowAnim = m_idleAnim;
}

Player::~Player()
{
}

void Player::Update()
{
	// ���x�N���A
	m_velocity = Vector2::Zero();

	// ���͂Ƃ�
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	// ���݂̏�Ԃ̏���
	(this->*m_state)(input, axis);

	// ������Update�͓��͂Ȃǂŗ͂��Z�o���I�������Ɏ��s���邱�ƁB
	m_velocity = m_physics->Update();

	CollideToMapChips();

	// ������Ԃ̑J��
	// ����e��Ԃɐݒu�����������򌸂�̂ł�
	if (CheckEnvironmentChanged())
	{
		// �n�と����
		if (m_physics->CheckState(MapConstants::Environment::kGround))
		{
			m_physics->ChangeState(MapConstants::Environment::kWater);
			m_graphic = "N";
			m_physics->UseConstantForce(true);
			m_state = &Player::Normal;
		}
		// �������n��
		else
		{
			m_physics->ChangeState(MapConstants::Environment::kGround);
			m_graphic = "Jump";
			m_physics->UseConstantForce(true);
			if (input.IsPressed("Dash"))
			{
				m_physics->AddForce(kJumpForce);
			}
			m_state = &Player::Jump;
		}
	}

	// �Ō�Ɉړ�
	m_pos += m_velocity;

	m_nowAnim->Update();
}

void Player::Draw() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(kRaduis), 0xff0000);
	m_nowAnim->Draw(screenPos);
#if _DEBUG
	DrawFormatString(0, 15, 0x999999, "PlayerPos:x = %f, y = %f", m_pos.x, m_pos.y);
	DrawFormatString(0, 105, 0x999999, "screenPos:x = %f, y = %f", screenPos.x, screenPos.y);
	DrawFormatString(0, 120, 0x999999, "vel:x = %f, y = %f", m_velocity.x, m_velocity.y);
	DrawString(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), m_graphic.c_str(), 0x00ff00);
#endif
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

void Player::OnDamage(int damage)
{
	// �_���[�W��ԂȂ�H���Ȃ�
	if (CheckState(PlayerState::kDamage)) return;

	// ����Ȃ̂ł�����ł��傤��
	m_hp -= damage;
	printf("Player�̗̑�%d\n", m_hp);
	if (m_hp <= 0)
	{
		m_state = &Player::Death;
		m_graphic = "Death";
	}
	else
	{
		m_state = &Player::Damage;
		m_graphic = "Damage";
	}
}

void Player::AddForce(const Vector2& force)
{
	m_physics->AddForce(force);
}

void Player::Stop()
{
	m_physics->Stop();
}

void Player::OnAttack()
{
	// �U�������[�V�����ɐ؂�ւ�
	m_stateFrameCount = 0;
	m_state = &Player::Attacked;
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	m_graphic = "��������B";
	(this->*m_state)(input, axis);
	return;
}