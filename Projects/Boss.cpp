#include "Boss.h"
#include "Animation.h"
#include "CircleCollider.h"
#include "Camera.h"
#include "Physics.h"
#include "SceneController.h"
#include "SceneGame.h"
#include <cassert>
#include "MapConstants.h"
#include "BoxCollider.h"
#include "Player.h"

namespace
{
	const Vector2Int kAnimationImageSize(32, 32);
	const HitPoint kMaxHitPoint(5);
	const std::string kBossIdleAnimPass   = "SharkIdle.png";
	const std::string kBossAttackAnimPass = "SharkChase.png";
	const std::string kBossDamageAnimPass = "SharkDamage.png";
	constexpr int kPlaySpeed = 5;
	constexpr float kWeight = 5.0f;
	constexpr float kVolume = 5.0f;
	constexpr float kCircleColRadius = 20.0f;
	constexpr float kBodyWidth = 80.0f;
	constexpr float kBodyHeight = 60.0f;
	// �̂̃R���C�_�[�𒆐S����ǂꂾ�����炷��
	const Vector2 kHeadOffset = { 60, 0 };
	const Vector2 kBodyOffset = { 0, 0 };
	constexpr int kDamageStateCount = 120;
	constexpr int kAttackedStateCount = 30;
	// �U���܂ł̎��Ԃ̊�b����
	constexpr int kAttackInterval = 5;
	// �U�ꕝ
	constexpr int kAttackTimeVariation = 2;
	constexpr int kChargeTime = 120;
	constexpr int kAttackTime = 120;
	const Vector2 kRightHomePosition = { 80 * (15 - 8), 80 * (122 - 5) };
	const Vector2 kLeftHomePosition = { 80 * (3 - 8), 80 * (122 - 5) };
}

void Boss::Idle()
{
	++m_stateFrameCount;
	// �ʏ���
	// �A�j���[�V����
	if (m_stateFrameCount > Game::kFrameRate * m_attackInterval)
	{
		ChangeState(&Boss::Charge);
	}

	HitToPlayer();
}

void Boss::Charge()
{
	// �k����
	m_pos += static_cast<float>(GetRand(10) - 5);
	if (m_stateFrameCount > kChargeTime)
	{
		// �v���C���[�̕����ɓ˂�����(�Ƃ肠����)
		m_physics->AddForce((m_playerRef.GetPos() - m_pos).GetNormalize() * 5);
		ChangeState(&Boss::Attack);
	}
	HitToPlayer();
}

void Boss::Attack()
{
	// ���̎��͐�[�ɓ���������X�^��������
	// Attack���̃v���C���[�̈ʒu�Ɍ������ēːi
	// ��莞�Ԃ������猳�ɖ߂�
	if (m_stateFrameCount > kAttackTime)
	{
		// ��ʒu�ɖ߂肽��
		// �E���ɂ�����E�ɁA�����ɂ����獶��

		ChangeState(&Boss::Idle);
	}
}

void Boss::Stun()
{
	// �����ŐH�������_���[�W
}

void Boss::Attacked()
{
	++m_stateFrameCount;
	// �����蔻��̏��������Ȃ�
	if (m_stateFrameCount > kAttackedStateCount)
	{
		ChangeState(&Boss::Idle);
	}
}

void Boss::Damage()
{
	++m_stateFrameCount;
	// �H�炢���[�V����
	if (m_hp.IsDead())
	{
		ChangeState(&Boss::Death);
	}
	// ���_���[�W�͎󂯂Ȃ�
	if (m_stateFrameCount > kDamageStateCount)
	{
		// �߂�
		ChangeState(&Boss::Idle);
		m_nowAnim = m_idleAnim;
	}

	HitToPlayerSafety();
}

void Boss::Death()
{
	// ���S���[�V����
	GameClear();
}

void Boss::GameClear()
{
	std::shared_ptr<SceneGame> gameScene = std::dynamic_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene());
	// nullptr�Ȃ炱���Ŏ~�܂�
	// static_cast�Ŏ~�߂Ă��������A�������̕����G���[���b�Z�[�W�o�邵�ǂ�����
	assert(gameScene && "���݂̃V�[�����Q�[���V�[���ł͂Ȃ�");
	gameScene->GameClear();
}

void Boss::HitToPlayer()
{
	// ���̂����蔻��
	CollisionStatus headCollision = m_headCol->CheckHit(m_playerRef.GetCollider());
	if (headCollision.isCollide)
	{
		if (CheckIsPlayerAttackState())
		{
			// �����܂ŗ�����_���[�W
			m_hp -= 1;
			// ��ԑJ��
			ChangeState(&Boss::Damage);
			// �v���C���[�Ɂu�U�������v�Ƌ�����
			m_playerRef.OnAttack();
			// �����m�b�N�o�b�N
			m_physics->AddForce(headCollision.overlap.GetNormalize());
			m_nowAnim = m_damageAnim;
		}
		else
		{
			// �v���C���[�Ƀ_���[�W
			m_playerRef.OnDamage();
			// �H��킵������
			ChangeState(&Boss::Attacked);
		}
		// �v���C���[�m�b�N�o�b�N
		m_playerRef.Stop();
		m_playerRef.AddForce(-headCollision.overlap.GetNormalize());

		// ���̌�̏����͍s��Ȃ�
		return;
	}

	// �̂̓����蔻��
	CollisionStatus bodyCollision = m_bodyCol->CheckHit(m_playerRef.GetCollider(), m_playerRef.GetVel());
	if (bodyCollision.isCollide)
	{
		// �v���C���[���U����ԂłȂ����
		if (!CheckIsPlayerAttackState())
		{
			// �v���C���[���_���[�W���󂯂�
			m_playerRef.OnDamage();
		}
		ChangeState(&Boss::Attacked);
		m_playerRef.Stop();
		m_playerRef.AddForce(-bodyCollision.overlap.GetNormalize() * 10);
	}
}

void Boss::HitToPlayerSafety()
{
	// ���̂����蔻��
	CollisionStatus headCollision = m_headCol->CheckHit(m_playerRef.GetCollider());
	if (headCollision.isCollide)
	{
		// �v���C���[�m�b�N�o�b�N
		m_playerRef.Stop();
		m_playerRef.AddForce(-headCollision.overlap.GetNormalize());

		// ���̌�̏����͍s��Ȃ�
		return;
	}

	// �̂̓����蔻��
	CollisionStatus bodyCollision = m_bodyCol->CheckHit(m_playerRef.GetCollider(), m_playerRef.GetVel());
	if (bodyCollision.isCollide)
	{
		// �m�b�N�o�b�N���邾��
		m_playerRef.Stop();
		m_playerRef.AddForce(-bodyCollision.overlap.GetNormalize() * 10);
	}
}

bool Boss::CheckIsPlayerAttackState()
{
	// ���o�Ă�����֐���
	return m_playerRef.CheckState(PlayerState::kAttack) || m_playerRef.CheckState(PlayerState::kStrongAttack);
}

void Boss::ChangeState(StateFunc_t nextState)
{
	m_stateFrameCount = 0;
	m_state = nextState;
}

void Boss::SetAttackInterval()
{
	m_attackInterval = GetRand(kAttackInterval + kAttackTimeVariation) - kAttackTimeVariation;
}

Boss::Boss(ObjectsController& cont, Player& player, Camera& camera, const Vector2& initPos, const Vector2Int& baseMapPos) :
	Enemy(cont, player, camera, initPos, baseMapPos),
	m_stateFrameCount(0),
	m_state(&Boss::Idle)
{
	m_idleAnim = std::make_shared<Animation>();
	m_attackAnim = std::make_shared<Animation>();
	m_damageAnim = std::make_shared<Animation>();

	m_idleAnim->Init(kBossIdleAnimPass, kAnimationImageSize, kPlaySpeed);
	m_attackAnim->Init(kBossAttackAnimPass, kAnimationImageSize, kPlaySpeed);
	m_damageAnim->Init(kBossDamageAnimPass, kAnimationImageSize, kPlaySpeed);

	m_idleAnim->SetExRate(5.0f);
	m_attackAnim->SetExRate(5.0f);
	m_damageAnim->SetExRate(5.0f);

	m_nowAnim = m_idleAnim;

	m_physics = std::make_shared<Physics>(kWeight, kVolume);
	m_headCol = std::make_shared<CircleCollider>(m_pos, kCircleColRadius, kHeadOffset);
	m_bodyCol = std::make_shared<BoxCollider>(m_pos, kBodyWidth, kBodyHeight, kBodyOffset);

	m_physics->ChangeState(MapConstants::kEnvironment::kWater);
	m_physics->UseConstantForce(false);

	m_hp = kMaxHitPoint;
}

void Boss::Update()
{
	m_pos += m_physics->Update();
	m_nowAnim->Update();
	(this->*m_state)();
}

void Boss::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_nowAnim->Draw(drawPos);

#if _DEBUG
	m_headCol->DrawColliderRange_Debug(m_camera.DrawOffset());
	m_bodyCol->DrawColliderRange_Debug(m_camera.DrawOffset());
#endif
}