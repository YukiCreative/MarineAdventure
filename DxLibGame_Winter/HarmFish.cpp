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

namespace
{
	constexpr int   kInitHp = 2;
	constexpr float kColRadius = 20.0f;
	constexpr int   kDamageStateFrame = 60;
	constexpr int   kAttackedStateFrame = 60;

	// プレイヤー追跡関連
	constexpr int   kChaseScoreMin = 0;
	constexpr int   kChaseScoreMax = 100;
	constexpr int   kChasePointIncreaseThreshold = 10000;
	constexpr int   kChasePointDecreaseThreshold = 100000;
	constexpr float kMoveForce = 0.1f;

	const std::string kIdleAnimFile      = "SharkIdle.png";
	const std::string kChaseAnimFile     = "SharkChase.png";
	const std::string kDamageAnimFile    = "SharkDamage.png";
	constexpr int     kImageOneSize      = 32;
	const Vector2Int  kImageSize(kImageOneSize, kImageOneSize);
	constexpr int     kIdleAnimPlaySpeed = 9;
	constexpr float   kGraphExpandRate   = MapConstants::kChipSize / kImageOneSize;
}

void HarmFish::Idle()
{
	// 当たり判定
	HitToPlayer();
	ChangeDirection();

	// プレイヤーが地上にいたら追尾には移行しない
	if (m_playerRef.IsGround()) return;

	// 追尾状態への遷移
	m_chasePoint += ScoreChasePoint();
	ChasePointValidation();
	if (m_chasePoint == kChaseScoreMax)
	{
		// これがどんな状態でも一つの関数でできたらいいのだが…
		m_state   = &HarmFish::Chase;
		m_nowAnim = m_chaseAnim;
		return;
	}
}

void HarmFish::Chase()
{
	// 遷移
	m_chasePoint += ScoreChasePoint();
	ChasePointValidation();
	if (m_chasePoint == kChaseScoreMin || m_playerRef.IsGround())
	{
		ChangeStateIdle();
		return;
	}

	// プレイヤーを追いかける
	Vector2 directionToPlayer = (m_playerRef.GetPos() - m_pos).GetNormalize();
	Vector2 moveForce = directionToPlayer * kMoveForce;
	m_physics->AddForce(moveForce);

	ChangeDirection();
	HitToPlayer();
}

void HarmFish::Attacked()
{
	// 何もしない時間
	if (m_stateFrameCount > kAttackedStateFrame)
	{
		ChangeStateIdle();
	}
}

void HarmFish::Damage()
{
	// 0になったらDeath
	if (m_hp.Value() == 0)
	{
		ChangeState(&HarmFish::Death);
		return;
	}
	// アニメーションしたい
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
		// 消える
		m_isDeleted = true;
		return;
	}
}

int HarmFish::ScoreChasePoint()
{
	float rerativeLength = (m_playerRef.GetPos() - m_pos).SqrMagnitude();
	// 段階的に実装するしかないか…？
	// ブレークポイントを置きたいので改行してる
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
	// Playerとの接触判定をする
	CollisionStatus collision = m_collider->CheckHit(m_playerRef.GetCollider());
	if (collision.isCollide)
	{
		// もしPlayerの状態が攻撃状態なら
		if (m_playerRef.CheckState(PlayerState::kAttack) || m_playerRef.CheckState(PlayerState::kStrongAttack))
		{
			// ここでHPを減らす
			m_hp.Decrease(1);
			printf("HP%dになたよ", m_hp.Value());
			ChangeState(&HarmFish::Damage);
			m_nowAnim = m_damageAnim;
			ChangeDirection();
			// プレイヤーに「攻撃した」と教える
			m_playerRef.OnAttack();
		}
		else
		{
			// ここでプレイヤーにダメージを教えてあげる
			m_playerRef.OnDamage();
			m_nowAnim = m_idleAnim;
			ChangeState(&HarmFish::Attacked);
		}
		// どちらにせよ両者をぶっ飛ばす
		m_playerRef.Stop();
		m_playerRef.AddForce(-collision.overlap.GetNormalize());
		m_physics->Stop();
		m_physics->AddForce(collision.overlap.GetNormalize());
	}
}

void HarmFish::ChangeDirection()
{
	// 今の速度に応じて、向きを変える
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

HarmFish::HarmFish(Player& player, Camera& camera, Vector2 spawnPos) :
	Enemy(player, camera, spawnPos),
	m_state(&HarmFish::Idle),
	m_stateFrameCount(0),
	m_chasePoint(0)
{
	// 生焼けになるけど大丈夫かな
	m_physics = std::make_shared<Physics>(1.0f, 1.0f);
	m_physics->UseConstantForce(false);
	m_collider = std::make_shared<CircleCollider>(m_pos, kColRadius);
	m_hp.Increase(kInitHp);

	// アニメーションの初期化
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
	// 状態に応じた処理を
	(this->*m_state)();

	m_pos += m_physics->Update();
	m_nowAnim->Update();

	// Updateの結果、画面外に出たら死亡
	if (CheckScreenOut())
	{
		m_isDeleted = true;
	}
}

void HarmFish::Draw() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);

	m_nowAnim->Draw(screenPos);
#if _DEBUG
	// 追跡範囲の描画
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), sqrt(kChasePointIncreaseThreshold), 0xffffff, false);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), sqrt(kChasePointDecreaseThreshold), 0xffffff, false);
	m_collider->DrawColliderRange_Debug(screenPos);
	DrawFormatString(0, 0, 0xffffff, "今の追尾評価値:%d\n", m_chasePoint);
#endif
}