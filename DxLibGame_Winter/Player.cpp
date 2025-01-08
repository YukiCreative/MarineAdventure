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
#include "TestScene.h"
#include "SoundManager.h"

namespace
{
	// �v���C���[�̓����蔻��Ɏg���܂�
	constexpr float kRaduis = 20.0f;
	constexpr int   kMaxHp  = 5;
	// Axis���ł�������񂾂�
	constexpr float      kMoveForceFactor        = 0.0002f;
	constexpr float      kJumpingMoveForceFactor = 0.0001f;
	constexpr float      kDashForceFactor        = 0.0003f;
	constexpr float      kStrongAttackMoveFactor = 0.0001f;
	constexpr float      kAttackFrame            = 60.0f;
	constexpr float      kInvincibleFrame        = 90.0f;
	constexpr float      kAttackedRigidFrame     = 30.0f;
	constexpr float      kStrongAttackForce      = 20.0f;
	constexpr float      kBounceFactor           = 1.2f;
	constexpr int        kMoveThreshold          = 10000;
	constexpr int		 kGroundMoveThreshold	 = 100;

	const Vector2    kJumpForce      (0.0f, -10.0f);
	const Vector2    kWaterJumpForce (0.0f,  -5.0f);
	const Vector2    kDashJumpForce  (0.0f, -12.0f);
	const Vector2Int kPlayerGraphSize(32, 32);
	// ���n�ł���n�ʂ̊p�x(�@��)
	constexpr int kLandingThresholdMin = 45;
	constexpr int kLandingThresholdMax = 135;

	const std::string kIdleAnimPath = "Idle (32x32).png";
}

void Player::GameOver()
{
	std::shared_ptr<TestScene> gameScene = std::dynamic_pointer_cast<TestScene>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "�Q�[���V�[���ɓ��I�L���X�g�ł��Ȃ�����");
	gameScene->GameOver();
}

// �������삳��Ă��Ȃ���ԁB
void Player::Normal(Input& input, Vector2& axis)
{
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger("Attack"))
	{
		m_graphic = "A";
		m_physics->UseConstantForce(false);
		ChangeState(&Player::Attack);
		 // ���̏�Ԃ̓��e�����s
		return;
	}
	// �X�e�B�b�N��Move��
	if (axis.SqrMagnitude() > kMoveThreshold)
	{
		m_graphic = "M";
		m_physics->UseConstantForce(false);
		ChangeState(&Player::Move);
		 // ���̏�Ԃ̓��e�����s
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
		ChangeState(&Player::Dash);
		 // ���̏�Ԃ̓��e�����s
		return;
	}
	// ���͂��Ȃ�������Nomal��
	if (axis.SqrMagnitude() < kMoveThreshold)
	{
		SetStateNormal();
		 // ���̏�Ԃ̓��e�����s
		return;
	}
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger("Attack"))
	{
		m_graphic = "SA";
		m_physics->UseConstantForce(false);
		// �����ŗ͂�������
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		ChangeState(&Player::StrongAttack);
		 // ���̏�Ԃ̓��e�����s
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
		ChangeState(&Player::Move);
		 // ���̏�Ԃ̓��e�����s
		return;
	}
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger("Attack"))
	{
		m_graphic = "SA";
		m_physics->UseConstantForce(false);
		// �����ŗ͂�������
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		ChangeState(&Player::Attack);
		 // ���̏�Ԃ̓��e�����s
		return;
	}
	// 	// ���͂��Ȃ�������Nomal��
	if (axis.SqrMagnitude() < kMoveThreshold)
	{
		SetStateNormal();
		 // ���̏�Ԃ̓��e�����s
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
	if (m_stateFrameCount >= kAttackFrame)
	{
		SetStateNormal();
		 // ���̏�Ԃ̓��e�����s
		return;
	}
	// �ړ����ł���
	m_physics->AddForce(axis * kMoveForceFactor);
}

void Player::StrongAttack(Input& input, Vector2& axis)
{
	// ��莞�Ԍo������Normal��
	if (m_stateFrameCount >= kAttackFrame)
	{
		SetStateNormal();
		 // ���̏�Ԃ̓��e�����s
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
	if (m_stateFrameCount >= kInvincibleFrame)
	{
		SetStateNormal();
		 // ���̏�Ԃ̓��e�����s
		return;
	}
}

void Player::Death(Input& input, Vector2& axis)
{
	// ���S���[�V����
	// �I�������ʂ̃V�[����
	GameOver();
}

void Player::Attacked(Input& input, Vector2& axis)
{
	// �d���Ȃ̂Ń��[�V�����ȊO�������Ȃ�
	if (m_stateFrameCount >= kAttackedRigidFrame)
	{
		SetStateNormal();
		return;
	}
}

void Player::GNormal(Input& input, Vector2& axis)
{
	// ���낢��ȃ��[�V�����ɂȂ���
	if (input.IsTrigger("Jump"))
	{
		m_graphic = "Jump";
		m_physics->AddForce(kJumpForce);
		ChangeState(&Player::Jump);
		return;
	}
	if (abs(axis.x) > kGroundMoveThreshold)
	{
		m_graphic = "GM";
		ChangeState(&Player::GMove);
		return;
	}
}

void Player::GMove(Input& input, Vector2& axis)
{
	if (input.IsTrigger("Jump"))
	{
		m_physics->AddForce(kJumpForce);
		m_graphic = "Jump";
		ChangeState(&Player::Jump);
		return;
	}
	if (abs(axis.x) < kGroundMoveThreshold)
	{
		m_graphic = "GN";
		ChangeState(&Player::GNormal);
		return;
	}
	if (input.IsPressed("Dash"))
	{
		m_graphic = "GD";
		ChangeState(&Player::GDash);
		return;
	}
	// ����������
	m_physics->AddForce(axis.x * kMoveForceFactor);
}

void Player::GDash(Input& input, Vector2& axis)
{
	// ���͂��Ȃ��Ȃ�����ʏ�ړ���
	if (!input.IsPressed("Dash"))
	{
		m_graphic = "GN";
		ChangeState(&Player::GMove);
		return;
	}
	// ���͂��Ȃ��Ȃ�����ʏ��Ԃ�
	if (abs(axis.x) < kGroundMoveThreshold)
	{
		m_graphic = "GN";
		ChangeState(&Player::GNormal);
		return;
	}
	if (input.IsTrigger("Jump"))
	{
		// �_�b�V���W�����v�͂�����ƍ�����т���
		m_physics->AddForce(kDashJumpForce);
		m_graphic = "Jump";
		ChangeState(&Player::Jump);
		return;
	}
	// ����������
	m_physics->AddForce(axis.x * kDashForceFactor);
}

void Player::Jump(Input& input, Vector2& axis)
{
	// �󒆃��[�V����
	// ���E�ɓ�����
	Vector2 sideAxis = Vector2(axis.x, 0.0f);
	// �W�����v�̑J�ڂ͑��݂��Ȃ��̂ŁA���i�W�����v���Ȃ�
	// ���n������GNormal��
	for (const auto& overlap : m_overlaps)
	{
		float angle = overlap.Angle();
		if (angle > kLandingThresholdMin && angle < kLandingThresholdMax)
		{
			m_graphic = "GN";
			ChangeState(&Player::GNormal);
			return;
		}
	}
	m_physics->AddForce(sideAxis * kJumpingMoveForceFactor);
	// �����͖ԗ��ł��Ă���
}

void Player::SetStateNormal()
{
	// ��ԑJ�ڂ��鏈�����d�����Ă����̂�
	m_graphic = "N";
	m_physics->UseConstantForce(true);
	ChangeState(&Player::Normal);
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
	m_overlaps.clear();

	// �}�b�v�Ƃ̏Փˏ����𕪂���
	auto& collidableMapChips = m_map.lock()->GetCollidableMapChips();
	Vector2 pushBackVec = Vector2::Zero();
	for (const auto& chip : collidableMapChips)
	{
		CollisionStatus col = m_collider->CheckHit(chip->GetCollider(), m_velocity);
		if (!col.isCollide) continue;

		// �F��ς��Ă݂�
		//chip->ChangeGraph_Debug();

		// �߂荞�݂��L�^
		m_overlaps.push_back(col.overlap);

		//// �ǂɋz���t���悤�ȋ����ɂȂ��Ĉ�a��������̂ŗ͂�������
		Vector2 overlapN = col.overlap.GetNormalize();
		//// ���݂̑��x�̕��A�������Ă���ǂ̌��������͂�������
		Vector2 addforce(m_velocity.x * std::abs(overlapN.x), m_velocity.y * std::abs(overlapN.y));
		m_physics->AddForce(-addforce * kBounceFactor);

		m_velocity -= col.overlap;
	}
}

void Player::ChangeState(StateFunc_t nextState)
{
	m_stateFrameCount = 0;
	m_state = nextState;
	// �X�e�[�g�̎��s�͂��Ȃ�
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

	++m_stateFrameCount;
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

			SoundManager::GetInstance().Play("���o�b�V��_3.mp3");
			SoundManager::GetInstance().Play("�����ɔ�э��މ�.mp3");
		}
		// �������n��
		else
		{
			m_physics->ChangeState(MapConstants::Environment::kGround);
			m_graphic = "Jump";
			m_physics->UseConstantForce(true);
			if (CheckState(PlayerState::kDash))
			{
				m_physics->AddForce(kWaterJumpForce);
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
	m_nowAnim->Draw(screenPos);
#if _DEBUG
	DrawString(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), m_graphic.c_str(), 0x00ff00);
	m_collider->DrawColliderRange_Debug(m_camera.DrawOffset());
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
	ChangeState(&Player::Attacked);
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	m_graphic = "��������B";
	return;
}