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
	// 体のコライダーを中心からどれだけずらすか
	const Vector2 kHeadOffset = { 60, 0 };
	const Vector2 kBodyOffset = { 0, 0 };
	constexpr int kDamageStateCount = 120;
	constexpr int kAttackedStateCount = 30;
	// 攻撃までの時間の基礎時間
	constexpr int kAttackInterval = 5;
	// 振れ幅
	constexpr int kAttackTimeVariation = 2;
	constexpr int kChargeTime = 120;
	constexpr int kAttackTime = 120;
	const Vector2 kRightHomePosition = { 80 * (15 - 8), 80 * (122 - 5) };
	const Vector2 kLeftHomePosition = { 80 * (3 - 8), 80 * (122 - 5) };
}

void Boss::Idle()
{
	++m_stateFrameCount;
	// 通常状態
	// アニメーション
	if (m_stateFrameCount > Game::kFrameRate * m_attackInterval)
	{
		ChangeState(&Boss::Charge);
	}

	HitToPlayer();
}

void Boss::Charge()
{
	// 震える
	m_pos += static_cast<float>(GetRand(10) - 5);
	if (m_stateFrameCount > kChargeTime)
	{
		// プレイヤーの方向に突っ込む(とりあえず)
		m_physics->AddForce((m_playerRef.GetPos() - m_pos).GetNormalize() * 5);
		ChangeState(&Boss::Attack);
	}
	HitToPlayer();
}

void Boss::Attack()
{
	// この時は先端に当たったらスタンしたい
	// Attack時のプレイヤーの位置に向かって突進
	// 一定時間たったら元に戻る
	if (m_stateFrameCount > kAttackTime)
	{
		// 定位置に戻りたい
		// 右側にいたら右に、左側にいたら左に

		ChangeState(&Boss::Idle);
	}
}

void Boss::Stun()
{
	// ここで食らったらダメージ
}

void Boss::Attacked()
{
	++m_stateFrameCount;
	// 当たり判定の処理をしない
	if (m_stateFrameCount > kAttackedStateCount)
	{
		ChangeState(&Boss::Idle);
	}
}

void Boss::Damage()
{
	++m_stateFrameCount;
	// 食らいモーション
	if (m_hp.IsDead())
	{
		ChangeState(&Boss::Death);
	}
	// 今ダメージは受けない
	if (m_stateFrameCount > kDamageStateCount)
	{
		// 戻る
		ChangeState(&Boss::Idle);
		m_nowAnim = m_idleAnim;
	}

	HitToPlayerSafety();
}

void Boss::Death()
{
	// 死亡モーション
	GameClear();
}

void Boss::GameClear()
{
	std::shared_ptr<SceneGame> gameScene = std::dynamic_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene());
	// nullptrならここで止まる
	// static_castで止めてもいいが、こっちの方がエラーメッセージ出るし良いかも
	assert(gameScene && "現在のシーンがゲームシーンではない");
	gameScene->GameClear();
}

void Boss::HitToPlayer()
{
	// 頭のあたり判定
	CollisionStatus headCollision = m_headCol->CheckHit(m_playerRef.GetCollider());
	if (headCollision.isCollide)
	{
		if (CheckIsPlayerAttackState())
		{
			// ここまで来たらダメージ
			m_hp -= 1;
			// 状態遷移
			ChangeState(&Boss::Damage);
			// プレイヤーに「攻撃した」と教える
			m_playerRef.OnAttack();
			// 自分ノックバック
			m_physics->AddForce(headCollision.overlap.GetNormalize());
			m_nowAnim = m_damageAnim;
		}
		else
		{
			// プレイヤーにダメージ
			m_playerRef.OnDamage();
			// 食らわしたった
			ChangeState(&Boss::Attacked);
		}
		// プレイヤーノックバック
		m_playerRef.Stop();
		m_playerRef.AddForce(-headCollision.overlap.GetNormalize());

		// この後の処理は行わない
		return;
	}

	// 体の当たり判定
	CollisionStatus bodyCollision = m_bodyCol->CheckHit(m_playerRef.GetCollider(), m_playerRef.GetVel());
	if (bodyCollision.isCollide)
	{
		// プレイヤーが攻撃状態でなければ
		if (!CheckIsPlayerAttackState())
		{
			// プレイヤーがダメージを受ける
			m_playerRef.OnDamage();
		}
		ChangeState(&Boss::Attacked);
		m_playerRef.Stop();
		m_playerRef.AddForce(-bodyCollision.overlap.GetNormalize() * 10);
	}
}

void Boss::HitToPlayerSafety()
{
	// 頭のあたり判定
	CollisionStatus headCollision = m_headCol->CheckHit(m_playerRef.GetCollider());
	if (headCollision.isCollide)
	{
		// プレイヤーノックバック
		m_playerRef.Stop();
		m_playerRef.AddForce(-headCollision.overlap.GetNormalize());

		// この後の処理は行わない
		return;
	}

	// 体の当たり判定
	CollisionStatus bodyCollision = m_bodyCol->CheckHit(m_playerRef.GetCollider(), m_playerRef.GetVel());
	if (bodyCollision.isCollide)
	{
		// ノックバックするだけ
		m_playerRef.Stop();
		m_playerRef.AddForce(-bodyCollision.overlap.GetNormalize() * 10);
	}
}

bool Boss::CheckIsPlayerAttackState()
{
	// 二回出てきたら関数化
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