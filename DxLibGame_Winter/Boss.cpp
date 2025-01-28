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
	const std::string kBossIdleAnimPass = "PlayerIdle.png";
	constexpr float kWeight = 5.0f;
	constexpr float kVolume = 5.0f;
	constexpr float kCircleColRadius = 20.0f;
	constexpr float kBodyWidth = 80.0f;
	constexpr float kBodyHeight = 60.0f;
	// 体のコライダーを中心からどれだけずらすか
	const Vector2 kBodyOffset(0, 50);
	constexpr int kDamageStateCount = 120;
	constexpr int kAttackedStateCount = 30;
}

void Boss::Idle()
{
	++m_stateFrameCount;
	// 通常状態
	// アニメーション
	
	// 体の当たり判定
	CollisionStatus bodyCollision = m_bodyCol->CheckHit(m_playerRef.GetCollider(), m_playerRef.GetVel());
	if (bodyCollision.isCollide)
	{
		if (CheckIsPlayerAttackState())
		{
			// プレイヤーはダメージを受けずに仕切り直し
			m_playerRef.Stop();
			m_playerRef.AddForce(-bodyCollision.overlap.GetNormalize() * 10);
			ChangeState(&Boss::Attacked);
		}
		else
		{
			// プレイヤーがダメージを受ける
			m_playerRef.OnDamage();
			// プレイヤーノックバック
			m_playerRef.AddForce(-bodyCollision.overlap.GetNormalize() * 10);
			ChangeState(&Boss::Attacked);
		}
		// この後の処理は行わない
		return;
	}

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
	}
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
	}
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

Boss::Boss(ObjectsController& cont, Player& player, Camera& camera, const Vector2& initPos, const Vector2Int& baseMapPos) :
	Enemy(cont, player, camera, initPos, baseMapPos),
	m_stateFrameCount(0),
	m_state(&Boss::Idle)
{
	m_idleAnim = std::make_shared<Animation>();
	m_idleAnim->Init(kBossIdleAnimPass, kAnimationImageSize, 1);
	m_nowAnim = m_idleAnim;
	m_physics = std::make_shared<Physics>(kWeight, kVolume);
	m_headCol = std::make_shared<CircleCollider>(m_pos, kCircleColRadius);
	m_bodyCol = std::make_shared<BoxCollider>(m_pos, kBodyWidth, kBodyHeight, kBodyOffset);

	m_physics->ChangeState(MapConstants::Environment::kWater);
	m_physics->UseConstantForce(false);

	m_hp = kMaxHitPoint;
}

void Boss::Update()
{
	m_pos += m_physics->Update();
	m_idleAnim->Update();
	(this->*m_state)();
}

void Boss::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_idleAnim->Draw(drawPos);

#if _DEBUG
	m_headCol->DrawColliderRange_Debug(m_camera.DrawOffset());
	m_bodyCol->DrawColliderRange_Debug(m_camera.DrawOffset());
#endif
}