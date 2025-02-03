#include "Animation.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "CircleCollider.h"
#include "game.h"
#include "GameEffect.h"
#include "HPUI.h"
#include "ImageStore.h"
#include "Input.h"
#include "MapChip.h"
#include "MapSystem.h"
#include "ObjectsController.h"
#include "Physics.h"
#include "Player.h"
#include "SceneController.h"
#include "SceneGame.h"
#include "Sound.h"
#include "SoundManager.h"
#include <cassert>
#include <DxLib.h>

namespace
{
	// �v���C���[�̓����蔻��Ɏg���܂�
	constexpr float kColliderRaduis = 30.0f;
	constexpr int   kMaxHp = 5;
	// Axis���ł�������񂾂�
	constexpr float  kMoveForceFactor = 0.0002f;
	constexpr float  kJumpingMoveForceFactor = 0.0001f;
	constexpr float  kDashForceFactor = 0.0003f;
	constexpr float  kStrongAttackMoveFactor = 0.0001f;
	constexpr float  kDuringDamageMoveFactor = 0.0001f;

	constexpr float  kAttackFrame = 60.0f;
	constexpr float  kInvincibleFrame = 90.0f;
	constexpr float  kAttackedRigidFrame = 30.0f;
	constexpr int    kDeathRigidFrame = 120; // ����d��
	constexpr int    kDeathDisappearFrame = 60; // ���U
	constexpr float  kStrongAttackForce = 20.0f;
	constexpr float  kBounceFactor = 1.2f;
	constexpr int    kMoveThreshold = 10000;
	constexpr int	 kGroundMoveThreshold = 100;

	const Vector2    kJumpForce      = { 0.0f, -15.0f };
	const Vector2    kWaterJumpForce = { 0.0f, -7.0f  };
	const Vector2    kDashJumpForce  = { 0.0f, -20.0f };
	constexpr float  kFallThreshold  = 2.0f;
	// ���n�ł���n�ʂ̊p�x(�@��)
	constexpr int kLandingThresholdMin = 45;
	constexpr int kLandingThresholdMax = 135;
	// �A�j���[�V����
	const std::string kIdleAnimPath      = "PlayerIdle.png";
	const std::string kJumpAnimPath      = "PlayerJump.png";
	const std::string kFallAnimPath      = "PlayerFall.png";
	const std::string kDamageAnimPath    = "PlayerDamage.png";
	const std::string kAttackAnimPath    = "PlayerAttack.png";
	const std::string kWalkAnimPath      = "PlayerDash.png";
	const std::string kDashAnimPath      = "PlayerDash.png";
	const std::string kDeathAnimPath     = "PlayerDisappear.png";
	constexpr int     kAnimPlaySpeed     = 3;
	constexpr int     kDashAnimSpeed     = 1;
	const Vector2Int  kPlayerGraphSize   = { 32, 32 };
	const Vector2Int  kDeathGraphSize    = { 96, 96 };
	constexpr float   kPlayerGraphExRate = 80.0f / 32.0f;

	// ���̃t�@�C��
	const std::string kIntoWaterSound  = "IntoTheWater.wav";
	const std::string kOutOfWaterSound = "�����@�o�V��.mp3";
	const std::string kStunSound       = "Stun.wav";
	const std::string kAttackSound     = "���g���A�N�V����.mp3";
	const std::string kWalkSound1      = "�X���C���I��.mp3";
	const std::string kWalkSound2      = "�X���C���I��_2.mp3";
	const std::string kDeathSound      = "���@���X�g��.mp3";
	constexpr     int kWalkSoundSpan   = 20;
	constexpr     int kDashSoundSpan   = 10;

	// �G�t�F�N�g
	// ����ȂɕK�v�ȕϐ��������Ȃ�N���X���������������C������
	const std::string kDashEffectFile = "PlayerDashEffect.png";
	const Vector2Int kDashEffectImageSize = { 32, 32 };
	const Vector2 kLeftDashEffectOffset = { -20, 16 };
	const Vector2 kRightDashEffectOffset = { 20, 16 };
}

void Player::GameOver()
{
	std::shared_ptr<SceneGame> gameScene = std::dynamic_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "�Q�[���V�[���ɓ��I�L���X�g�ł��Ȃ�����");
	gameScene->GameOver();
}

// �������삳��Ă��Ȃ���ԁB
void Player::Normal(Input& input, Vector2& axis)
{
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger("Attack"))
	{
		m_stateText = "A";
		SetStateAttack();
		return;
	}
	// �X�e�B�b�N��Move��
	if (axis.SqrMagnitude() > kMoveThreshold)
	{
		m_stateText = "M";
		m_physics->UseConstantForce(false);
		ChangeState(&Player::Move);
		return;
	}
	// ���x�ɉ����Č�����ς���
	ChangeRotation();
}

// �ړ����Ă܂�
void Player::Move(Input& input, Vector2& axis)
{
	// �_�b�V��������Ă���Dash��
	if (input.IsPressed("Dash"))
	{
		m_stateText = "D";
		m_physics->UseConstantForce(false);
		ChangeState(&Player::Dash);
		 // ���̏�Ԃ̓��e�����s
		return;
	}
	// ���͂��Ȃ�������Nomal��
	if (axis.SqrMagnitude() < kMoveThreshold)
	{
		SetStateNormal();
		return;
	}
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger("Attack"))
	{
		m_stateText = "SA";
		// �����ŗ͂�������
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		SetStateAttack();
		return;
	}
	// ��
	m_physics->AddForce(axis * kMoveForceFactor);
	// ���݂̈ړ������ɂ���ă��[�V������ς���
	ChangeDirection(axis);
	// ���x�ɉ����Č�����ς���
	ChangeRotation();
}

// �����ł��B
void Player::Dash(Input& input, Vector2& axis)
{
	// �_�b�V��������ĂȂ�������Move��
	if (!input.IsPressed("Dash"))
	{
		m_stateText = "M";
		m_physics->UseConstantForce(false);
		ChangeState(&Player::Move);
		 // ���̏�Ԃ̓��e�����s
		return;
	}
	// B�{�^���ŃA�^�b�N���
	if (input.IsTrigger("Attack"))
	{
		m_stateText = "SA";
		// �����ŗ͂�������
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		SetStateAttack();
		return;
	}
	// 	// ���͂��Ȃ�������Nomal��
	if (axis.SqrMagnitude() < kMoveThreshold)
	{
		SetStateNormal();
		return;
	}
	// ��
	m_physics->AddForce(axis * kDashForceFactor);
	// ���[�V�������ς��̂͂����������
	ChangeDirection(axis);
	// ���x�ɉ����Č�����ς���
	ChangeRotation();
}

void Player::Attack(Input& input, Vector2& axis)
{
	// �U�����������
	// ��莞�Ԍo������Normal��
	if (m_stateFrameCount >= kAttackFrame)
	{
		SetStateNormal();
		ChangeAnimation(m_idleAnim);
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
		if (m_physics->CheckState(MapConstants::kEnvironment::kWater))
		{
			SetStateNormal();
		}
		else
		{
			m_nowAnim = m_idleAnim;
			ChangeState(&Player::GNormal);
			m_physics->UseConstantForce(true);
		}

		return;
	}
	// 01/14�@������悤��
	m_physics->AddForce(axis * kDuringDamageMoveFactor);
}

void Player::Death(Input& input, Vector2& axis)
{
	// ���S���[�V����
	if (m_stateFrameCount > kDeathRigidFrame)
	{
		m_nowAnim = m_deathAnim;
		SoundManager::GetInstance().Play(kDeathSound);
		ChangeState(&Player::DisAppear);
	}
}

void Player::DisAppear(Input& input, Vector2& axis)
{
	// �I�������ʂ̃V�[����
	if (m_stateFrameCount > kDeathDisappearFrame)
	{
		GameOver();
	}
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
		m_physics->AddForce(kJumpForce);
		SoundManager::GetInstance().Play("�t�@�j�[�W�����v_2.mp3");
		SetStateJump();
		return;
	}
	if (m_velocity.y > kFallThreshold)
	{
		// �W�����v�Ȃ��󒆏��
		SetStateJump();
		m_nowAnim = m_fallAnim;
		return;
	}
	if (abs(axis.x) > kGroundMoveThreshold)
	{
		m_stateText = "GM";
		ChangeState(&Player::GMove);
		ChangeAnimation(m_walkAnim);
		return;
	}
}

void Player::GMove(Input& input, Vector2& axis)
{
	// �L�����̌�����ς���
	ChangeDirection(axis);
	if (input.IsTrigger("Jump"))
	{
		m_physics->AddForce(kJumpForce);
		SoundManager::GetInstance().Play("�t�@�j�[�W�����v_2.mp3");
		SetStateJump();
		return;
	}
	if (m_velocity.y > kFallThreshold)
	{
		// �W�����v�Ȃ��󒆏��
		SetStateJump();
		m_nowAnim = m_fallAnim;
		return;
	}
	if (abs(axis.x) < kGroundMoveThreshold)
	{
		m_stateText = "GN";
		ChangeState(&Player::GNormal);
		ChangeAnimation(m_idleAnim);
		return;
	}
	if (input.IsPressed("Dash"))
	{
		m_stateText = "GD";
		ChangeState(&Player::GDash);
		Vector2 effectOffset = m_isLeft ? kRightDashEffectOffset : kLeftDashEffectOffset;
		auto effect = m_objCont.lock()->SpawnEffect(kDashEffectFile, kDashEffectImageSize, kAnimPlaySpeed, m_pos, effectOffset);
		// ���f�[�^���������Ȃ�ł���
		effect->ReverceX(!m_isLeft);
		effect->SetExRate(2.0f);
		ChangeAnimation(m_dashAnim);
		return;
	}
	// ����������
	m_physics->AddForce(axis.x * kMoveForceFactor);
	// ��莞�Ԃ��Ƃɑ�����炷
	if (!(m_stateFrameCount % kWalkSoundSpan)) PlayWalkSound();
}

void Player::GDash(Input& input, Vector2& axis)
{
	// ���͂��Ȃ��Ȃ�����ʏ�ړ���
	if (!input.IsPressed("Dash"))
	{
		m_stateText = "GN";
		ChangeState(&Player::GMove);
		ChangeAnimation(m_walkAnim);
		return;
	}
	// ���͂��Ȃ��Ȃ�����ʏ��Ԃ�
	if (abs(axis.x) < kGroundMoveThreshold)
	{
		m_stateText = "GN";
		ChangeState(&Player::GNormal);
		ChangeAnimation(m_idleAnim);
		return;
	}
	if (input.IsTrigger("Jump"))
	{
		// �_�b�V���W�����v�͂�����ƍ�����т���
		m_physics->AddForce(kDashJumpForce);
		SoundManager::GetInstance().Play("�t�@�j�[�W�����v_3.mp3");
		SetStateJump();
		return;
	}
	if (m_velocity.y > kFallThreshold)
	{
		SetStateJump();
		// �A�j���[�V�����̐؂�ւ����d�����Ă���̂��C�ɂȂ�
		m_nowAnim = m_fallAnim;
		return;
	}
	// ����������
	m_physics->AddForce(axis.x * kDashForceFactor);
	// �L�����̌�����ς���
	ChangeDirection(axis);
	// ��莞�Ԃ��Ƃɑ�����炷
	if (!(m_stateFrameCount % kDashSoundSpan)) PlayWalkSound();
}

void Player::Air(Input& input, Vector2& axis)
{
	// �󒆃��[�V����
	// ���E�ɓ�����
	Vector2 sideAxis = Vector2(axis.x, 0.0f);
	// ���n������GNormal��
	for (const auto& overlap : m_overlaps)
	{
		float angle = overlap.Angle();
		// continue���Â炢���Ȃ�
		if (angle < kLandingThresholdMin || angle > kLandingThresholdMax) continue;

		m_stateText = "GN";
		m_physics->IsGrounded(true);
		ChangeState(&Player::GNormal);
		ChangeAnimation(m_idleAnim);
		// �������[�V�������΂߂��Ă���ꍇ������̂Ō������Z�b�g
		m_nowAnim->SetRotate(0);
		return;
	}
	m_physics->AddForce(sideAxis * kJumpingMoveForceFactor);
	ChangeDirection(axis);
	ChangeFallAnim();
}

void Player::SetStateNormal()
{
	// ��ԑJ�ڂ��鏈�����d�����Ă����̂�
	m_stateText = "N";
	m_physics->UseConstantForce(true);
	ChangeAnimation(m_idleAnim);
	ChangeState(&Player::Normal);
}

void Player::SetStateAttack()
{
	m_physics->UseConstantForce(false);
	SoundManager::GetInstance().Play(kAttackSound);
	ChangeState(&Player::Attack);
	ChangeAnimation(m_attackAnim);
}

void Player::SetStateJump()
{
	m_stateText = "Jump";
	m_physics->IsGrounded(false);
	ChangeState(&Player::Air);
	ChangeAnimation(m_jumpAnim);
}

bool Player::CheckEnvironmentChanged()
{
	// ������񓖂��蔻�肷��
	// ���ׂẴ}�b�v�`�b�v���Ώ�
	const auto& allMapChips = m_map.lock()->GetAllMapChips();
	std::list<MapConstants::kEnvironment> hitEnvironments;
	for (const auto& chip : allMapChips)
	{
		// �ړ��Ȃ������蔻��
		// �����y��
		CollisionStatus col = m_collider->CheckHit(chip->GetCollider());
		if (!col.isCollide) continue;

		// Environment���L��
		hitEnvironments.push_back(chip->GetMapChipData().environment);
	}
	// �}�b�v�O�̏ꍇ�͍��̏�Ԃ���ς��Ȃ�
	if (hitEnvironments.empty()) return false;

	// �����������ɂ���ꍇ�A
	bool result = true;
	for (const auto& env : hitEnvironments)
	{
		result &= !m_physics->CheckState(env);
	}
	return result;
}

void Player::CollideToMapChips()
{
	Vector2 overlapSum;
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
		overlapSum += col.overlap;
	}

	// �ǂɋz���t���悤�ȋ����ɂȂ��Ĉ�a��������̂ŗ͂�������
	// �p�ɓ����������͖����ɂ�����
	Vector2 overlapN = overlapSum.GetNormalize();
	// ���݂̑��x�̕��A�������Ă���ǂ̌��������͂�������
	Vector2 addforce(m_velocity.x * std::abs(overlapN.x), m_velocity.y * std::abs(overlapN.y));
	m_physics->AddForce(-addforce * kBounceFactor);

	// �Ō�ɔ��f
	m_velocity -= overlapSum;
}

void Player::ChangeState(StateFunc_t nextState)
{
	m_stateFrameCount = 0;
	m_state = nextState;
	// �X�e�[�g�̎��s�͂��Ȃ�
}

void Player::ChangeAnimation(const std::shared_ptr<Animation>& setAnim)
{
	m_nowAnim = setAnim;
	m_nowAnim->ReverceX(m_isLeft);
}

void Player::ChangeDirection(const Vector2& axis)
{
	if (abs(axis.x) < kGroundMoveThreshold) return;
	m_isLeft = axis.x < 0;
	m_nowAnim->ReverceX(m_isLeft);
}

void Player::ChangeFallAnim()
{
	if (m_velocity.y > kFallThreshold)
	{
		m_nowAnim = m_fallAnim;
	}

	if (abs(m_velocity.x) < 0.1f) return;
	// ���̈ړ������ɉ����Č�����ς�����
	m_nowAnim->ReverceX(m_velocity.x < 0);
}

void Player::PlayWalkSound()
{
	// �s�b�`�������_���ɂ���������
	SoundManager::GetInstance().Play(GetRand(1) ? kWalkSound1 : kWalkSound2);
}

void Player::ChangeRotation()
{
	// ���x�ɉ����Č�����ς���
	m_nowAnim->SetRotate(m_physics->GetVel().Angle() + 90);
}

bool Player::CheckOutOfScreen()
{
	Vector2 screenPos = m_camera.Capture(m_pos);

	if (screenPos.x < 0                   + kColliderRaduis) return true;
	if (screenPos.x > Game::kScreenWidth  + kColliderRaduis) return true;
	if (screenPos.y < 0                   + kColliderRaduis) return true;
	if (screenPos.y > Game::kScreenHeight + kColliderRaduis) return true;

	return false;
}

void Player::InstantDeath()
{
	m_hpUI.OnDamage(5);
	ChangeState(&Player::Death);
}

Player::Player(Camera& camera, Vector2 spawnPos, HitPoints& hpUI) :
	GameObject(spawnPos),
	m_state(&Player::Normal),
	m_stateText("N"),
	m_stateFrameCount(0),
	m_hp(kMaxHp),
	m_camera(camera),
	m_isLeft(false),
	m_hpUI(hpUI)
{
	ImageStore& imageStore = ImageStore::GetInstance();
	m_physics  = std::make_shared<Physics>(1.0f, 1.0f),
	m_collider = std::make_shared<CircleCollider>(m_pos, kColliderRaduis);
	// ��������A�j���[�V�����̏�����
	// ������Ă܂Ƃ߂��ق��������̂��s�x�錾���ď������֐��������ق��������̂�
	m_idleAnim   = std::make_shared<Animation>();
	m_jumpAnim   = std::make_shared<Animation>();
	m_fallAnim   = std::make_shared<Animation>();
	m_damageAnim = std::make_shared<Animation>();
	m_attackAnim = std::make_shared<Animation>();
	m_walkAnim   = std::make_shared<Animation>();
	m_dashAnim   = std::make_shared<Animation>();
	m_deathAnim  = std::make_shared<Animation>();

	m_idleAnim  ->Init(kIdleAnimPath,   kPlayerGraphSize, kAnimPlaySpeed);
	m_jumpAnim  ->Init(kJumpAnimPath,   kPlayerGraphSize, kAnimPlaySpeed);
	m_fallAnim  ->Init(kFallAnimPath,   kPlayerGraphSize, kAnimPlaySpeed);
	m_damageAnim->Init(kDamageAnimPath, kPlayerGraphSize, kAnimPlaySpeed);
	m_attackAnim->Init(kAttackAnimPath, kPlayerGraphSize, kAnimPlaySpeed);
	m_walkAnim  ->Init(kWalkAnimPath,   kPlayerGraphSize, kAnimPlaySpeed);
	m_dashAnim  ->Init(kDashAnimPath,   kPlayerGraphSize, kDashAnimSpeed);
	m_deathAnim ->Init(kDeathAnimPath,  kDeathGraphSize,  10);

	m_idleAnim  ->SetExRate(kPlayerGraphExRate);
	m_jumpAnim  ->SetExRate(kPlayerGraphExRate);
	m_fallAnim  ->SetExRate(kPlayerGraphExRate);
	m_damageAnim->SetExRate(kPlayerGraphExRate);
	m_attackAnim->SetExRate(kPlayerGraphExRate);
	m_walkAnim  ->SetExRate(kPlayerGraphExRate);
	m_dashAnim  ->SetExRate(kPlayerGraphExRate);
	m_deathAnim ->SetExRate(kPlayerGraphExRate);

	m_nowAnim = m_idleAnim;
}

Player::~Player()
{
}

void Player::Init(std::weak_ptr<MapSystem> map, std::weak_ptr<ObjectsController> objCont)
{
	m_map = map;
	m_objCont = objCont;
}

void Player::Update()
{
	// ���͂Ƃ�
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();

	++m_stateFrameCount;
	// ���݂̏�Ԃ̏���
	(this->*m_state)(input, axis);

	// ���x�N���A
	m_velocity = Vector2::Zero();

	// ������Update�͓��͂Ȃǂŗ͂��Z�o���I�������Ɏ��s���邱�ƁB
	m_velocity = m_physics->Update();

	CollideToMapChips();

	// ������Ԃ̑J��
	// ����e��Ԃɐݒu�����������򌸂�̂ł�
	if (CheckEnvironmentChanged())
	{
		// �n�と����
		if (m_physics->CheckState(MapConstants::kEnvironment::kGround))
		{
			// ���낢�����Ă�Ȃ�
			m_physics->IsGrounded(false);
			m_physics->ChangeState(MapConstants::kEnvironment::kWater);
			SetStateNormal();
			SoundManager::GetInstance().Play(kIntoWaterSound);
			// ���̏Ռ��ŃX�s�[�h�������銴��
			m_physics->AddForce(-m_velocity * 0.5f);
		}
		// �������n��
		else
		{
			m_physics->ChangeState(MapConstants::kEnvironment::kGround);
			m_physics->UseConstantForce(true);
			if (CheckState(PlayerState::kDash)) { m_physics->AddForce(kWaterJumpForce); }
			SetStateJump();
			SoundManager::GetInstance().Play(kOutOfWaterSound);
		}
	}

	// �Ō�Ɉړ�
	m_pos += m_velocity;

	m_nowAnim->Update();

	if (CheckOutOfScreen())
	{
		InstantDeath();
	}
#if _DEBUG
	if (input.IsTrigger("RecoverPlayerHp_Debug"))
	{
		OnRecovery();
	}
	if (input.IsTrigger("DamagePlayer_Debug"))
	{
		OnDamage();
	}
#endif
}

void Player::AnimationUpdate()
{
	// ������󂯕t�����A�A�j���[�V�����������X�V
	m_nowAnim->Update();
}

void Player::Draw() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	m_nowAnim->Draw(screenPos);
#if _DEBUG
	DrawString(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), m_stateText.c_str(), 0x00ff00);
	m_collider->DrawColliderRange_Debug(m_camera.DrawOffset());

	for (const auto& overlap : m_overlaps)
	{
		DrawLine(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(screenPos.x + overlap.x * 5), static_cast<int>(screenPos.y + overlap.y * 5), 0x8fffff);
	}
	DrawLine(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(screenPos.x + m_velocity.x * 5), static_cast<int>(screenPos.y + m_velocity.y * 5), 0xff8fff);
	DrawBox(static_cast<int>(screenPos.x - kPlayerGraphSize.x * kPlayerGraphExRate / 2),
		static_cast<int>(screenPos.y - kPlayerGraphSize.y * kPlayerGraphExRate / 2),
		static_cast<int>(screenPos.x + kPlayerGraphSize.x * kPlayerGraphExRate / 2),
		static_cast<int>(screenPos.y + kPlayerGraphSize.y * kPlayerGraphExRate / 2),
		0xffffff, false);
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
#if _DEBUG
	printf("Player�̗̑�%d\n", m_hp.Value());
#endif
	if (m_hp.IsDead())
	{
		m_stateText = "Death";
		m_hpUI.OnDamage();
		ChangeState(&Player::Death);
	}
	else
	{
		m_stateText = "Damage";
		m_hpUI.OnDamage();
		ChangeState(&Player::Damage);
	}

	SoundManager::GetInstance().Play(kStunSound);
	ChangeAnimation(m_damageAnim);
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
	m_stateText = "��������B";
	return;
}

void Player::OnRecovery(const int recoverAmount)
{
	m_hp += recoverAmount;
	if (m_hp.Value() > kMaxHitPoint)
	{
		m_hp = kMaxHitPoint;
	}
	m_hpUI.OnRecovery(recoverAmount);
}

bool Player::IsGround()
{
	return m_physics->CheckState(MapConstants::kEnvironment::kGround);
}
