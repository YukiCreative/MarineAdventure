#include "HarmFish.h"
#include <DxLib.h>
#include "Camera.h"
#include <memory>
#include "Physics.h"
#include "Player.h"
#include "CircleCollider.h"
#include "Animation.h"
#include "MapConstants.h"
#include <algorithm>
#include "SoundManager.h"
#include "SceneController.h"
#include "Scene.h"

namespace
{
	constexpr int   kInitHp             = 2;
	constexpr float kColRadius          = 20.0f;
	constexpr int   kDamageStateFrame   = 60;
	constexpr int   kAttackedStateFrame = 60;

	// �v���C���[�ǐՊ֘A
	constexpr int   kChaseScoreMin               = 0;
	constexpr int   kChaseScoreMax               = 100;
	constexpr int   kChasePointIncreaseThreshold = 50000;
	constexpr int   kChasePointDecreaseThreshold = 300000;
	constexpr float kMoveForce                   = 0.1f;

	const std::string kIdleAnimFile      = "SharkIdle.png";
	const std::string kChaseAnimFile     = "SharkChase.png";
	const std::string kDamageAnimFile    = "SharkDamage.png";
	constexpr int     kImageOneSize      = 32;
	const Vector2Int  kImageSize(kImageOneSize, kImageOneSize);
	constexpr int     kIdleAnimPlaySpeed = 9;
	constexpr float   kGraphExpandRate   = MapConstants::kChipSize / kImageOneSize;

	// ��
	const std::string kDamageSound = "���g���A�N�V����_3.mp3";
}

void HarmFish::Idle()
{
	if (m_playerRef.CheckState(PlayerState::kDeath)) return;

	// �����蔻��
	HitToPlayer();
	ChangeDirection();

	// �v���C���[���n��ɂ�����ǔ��ɂ͈ڍs���Ȃ�
	if (m_playerRef.IsGround()) return;

	// �ǔ���Ԃւ̑J��
	m_chasePoint += ScoreChasePoint();
	ChasePointValidation();
	if (m_chasePoint == kChaseScoreMax)
	{
		// ���ꂪ�ǂ�ȏ�Ԃł���̊֐��łł����炢���̂����c
		m_state   = &HarmFish::Chase;
		m_nowAnim = m_chaseAnim;
		return;
	}
}

void HarmFish::Chase()
{
	// �J��
	m_chasePoint += ScoreChasePoint();
	ChasePointValidation();
	if (m_chasePoint == kChaseScoreMin || m_playerRef.IsGround())
	{
		ChangeStateIdle();
		return;
	}

	// �v���C���[��ǂ�������
	Vector2 directionToPlayer = (m_playerRef.GetPos() - m_pos).GetNormalize();
	Vector2 moveForce = directionToPlayer * kMoveForce;
	m_physics->AddForce(moveForce);

	ChangeDirection();
	HitToPlayer();
}

void HarmFish::Attacked()
{
	// �������Ȃ�����
	if (m_stateFrameCount > kAttackedStateFrame)
	{
		ChangeStateIdle();
	}

	ChangeDirection();
}

void HarmFish::Damage()
{
	// 0�ɂȂ�����Death
	if (m_hp.IsDead())
	{
		ChangeState(&HarmFish::Death);
		return;
	}
	// �A�j���[�V����������
	if (m_stateFrameCount > kDamageStateFrame)
	{
		ChangeStateIdle();
		return;
	}
}

void HarmFish::Death()
{
	if (m_stateFrameCount > kDamageStateFrame)
	{
		// ������
		m_isDeleted = true;
		return;
	}
}

int HarmFish::ScoreChasePoint()
{
	if (m_playerRef.CheckState(PlayerState::kDeath)) return -100;

	float rerativeLength = (m_playerRef.GetPos() - m_pos).SqrMagnitude();
	// �i�K�I�Ɏ������邵���Ȃ����c�H
	// �u���[�N�|�C���g��u�������̂ŉ��s���Ă�
	if (rerativeLength > kChasePointDecreaseThreshold)
	{
		return -1;
	}
	if (rerativeLength > kChasePointIncreaseThreshold)
	{
		return  1;
	}
	return 5;
}

void HarmFish::ChasePointValidation()
{
	m_chasePoint = std::clamp(m_chasePoint, kChaseScoreMin, kChaseScoreMax);
}

void HarmFish::HitToPlayer()
{
	// Player�Ƃ̐ڐG���������
	CollisionStatus collision = m_collider->CheckHit(m_playerRef.GetCollider());
	if (collision.isCollide)
	{
		// ����Player�̏�Ԃ��U����ԂȂ�
		if (m_playerRef.CheckState(PlayerState::kAttack) || m_playerRef.CheckState(PlayerState::kStrongAttack))
		{
			// ������HP�����炷
			m_hp -= 1;
#if _DEBUG
			printf("HP%d�ɂȂ���", m_hp.Value());
#endif
			ChangeState(&HarmFish::Damage);
			m_nowAnim = m_damageAnim;
			ChangeDirection();
			// �v���C���[�Ɂu�U�������v�Ƌ�����
			m_playerRef.OnAttack();
			SoundManager::GetInstance().Play(kDamageSound);

			m_physics->Stop();
			m_playerRef.Stop();
			m_physics->AddForce(collision.overlap.GetNormalize() * 10);
		}
		else
		{
			// �����Ńv���C���[�Ƀ_���[�W�������Ă�����
			m_playerRef.OnDamage();
			m_nowAnim = m_idleAnim;
			ChangeState(&HarmFish::Attacked);
			m_playerRef.Stop();
			m_physics->Stop();
			m_playerRef.AddForce(-collision.overlap.GetNormalize() * 5);
		}
	}
}

void HarmFish::HitToMap()
{
}

void HarmFish::ChangeDirection()
{
	// ���̑��x�ɉ����āA������ς���
	m_nowAnim->ReverceX(m_physics->GetVel().x < 0);
}

void HarmFish::ChangeState(StateFunc_t nextState)
{
	m_state = nextState;
	m_stateFrameCount = 0;
}

void HarmFish::ChangeStateIdle()
{
	ChangeState(&HarmFish::Idle);
	m_nowAnim = m_idleAnim;
	m_chasePoint = 0;
}

HarmFish::HarmFish(ObjectsController& cont, Player& player, Camera& camera, const Vector2& initPos, const Vector2Int& baseMapPos) :
	Enemy(cont, player, camera, initPos, baseMapPos),
	m_state(&HarmFish::Idle),
	m_stateFrameCount(0),
	m_chasePoint(0)
{
	// ���Ă��ɂȂ邯�Ǒ��v����
	m_physics = std::make_shared<Physics>(1.0f, 1.0f);
	m_physics->UseConstantForce(false);
	m_collider = std::make_shared<CircleCollider>(m_pos, kColRadius);
	m_hp += kInitHp;

	// �A�j���[�V�����̏�����
	m_idleAnim   = std::make_shared<Animation>();
	m_chaseAnim  = std::make_shared<Animation>();
	m_damageAnim = std::make_shared<Animation>();
	//m_deathAnim  = std::make_shared<Animation>();

	m_idleAnim  ->Init(kIdleAnimFile,   kImageSize, kIdleAnimPlaySpeed);
	m_chaseAnim ->Init(kChaseAnimFile,  kImageSize, kIdleAnimPlaySpeed);
	m_damageAnim->Init(kDamageAnimFile, kImageSize, kIdleAnimPlaySpeed);

	m_idleAnim  ->SetExRate(kGraphExpandRate);
	m_chaseAnim ->SetExRate(kGraphExpandRate);
	m_damageAnim->SetExRate(kGraphExpandRate);
	//m_deathAnim ->SetExRate(kGraphExpandRate);

	m_nowAnim = m_idleAnim;
}

void HarmFish::Update()
{
	++m_stateFrameCount;
	// ��Ԃɉ�����������
	(this->*m_state)();

	m_pos += m_physics->Update();
	m_nowAnim->Update();

	// Update�̌��ʁA��ʊO�ɏo���玀�S
	// 01/20�d�l�ύX�B��ʊO�ɏo�Ă����v�ɂȂ�܂���
}

void HarmFish::Draw() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);

	m_nowAnim->Draw(screenPos);
#if _DEBUG
	// �ǐՔ͈͂̕`��
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(sqrt(kChasePointIncreaseThreshold)), 0xffffff, false);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(sqrt(kChasePointDecreaseThreshold)), 0xffffff, false);
	m_collider->DrawColliderRange_Debug(m_camera.DrawOffset());
	DrawFormatString(0, 0, 0xffffff, "���̒ǔ��]���l:%d\n", m_chasePoint);
#endif
}