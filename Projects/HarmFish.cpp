#include "Animation.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "CircleCollider.h"
#include "HarmFish.h"
#include "MapChip.h"
#include "MapConstants.h"
#include "MapSystem.h"
#include "ObjectsController.h"
#include "Physics.h"
#include "Player.h"
#include "SceneController.h"
#include "SceneGame.h"
#include "SoundManager.h"
#include <algorithm>
#include <DxLib.h>
#include <memory>
#include "Statistics.h"

namespace
{
	constexpr int   kInitHp             = 2;
	constexpr float kColRadius          = 20.0f;
	constexpr int   kDamageStateFrame   = 60;
	constexpr int   kAttackedStateFrame = 60;

	// プレイヤー追跡関連
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

	// 音
	const std::string kDamageSound = "DamageSound.mp3";
}

void HarmFish::Idle()
{
	if (m_playerRef.CheckState(PlayerState::kDeath)) return;

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

	ChangeDirection();
}

void HarmFish::Damage()
{
	// 0になったらDeath
	if (m_hp.IsDead())
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
		Statistics::GetInstance().KilledEnemy();
		return;
	}
}

int HarmFish::ScoreChasePoint()
{
	if (m_playerRef.CheckState(PlayerState::kDeath)) return -100;

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
			m_hp -= 1;
#if _DEBUG
			printf("HP%dになたよ", m_hp.Value());
#endif
			ChangeState(&HarmFish::Damage);
			m_nowAnim = m_damageAnim;
			ChangeDirection();
			// プレイヤーに「攻撃した」と教える
			m_playerRef.OnAttack();
			SoundManager::GetInstance().Play(kDamageSound);

			m_physics->Stop();
			m_playerRef.Stop();
			m_physics->AddForce(collision.overlap.GetNormalize() * 10);
			m_scene->ScreenShake(30);
			m_scene->HitStop(30);
		}
		else
		{
			// ここでプレイヤーにダメージを教えてあげる
			m_playerRef.OnDamage();
			m_nowAnim = m_idleAnim;
			ChangeState(&HarmFish::Attacked);
			m_playerRef.Stop();
			m_physics->Stop();
			m_playerRef.AddForce(-collision.overlap.GetNormalize() * 5);
			m_scene->ScreenShake(30);
			m_scene->HitStop(30);
		}
	}
}

void HarmFish::HitToMap()
{
	// マップくれ
	MapSystem& map = m_scene->GetMap();
	std::list<MapConstants::kEnvironment> hitEnvironments;
	for (const auto& chip : map.GetCollidableMapChips())
	{
		CollisionStatus collision = m_collider->CheckHit(chip->GetCollider());
		if (!collision.isCollide) continue;

		m_pos += collision.overlap;
		m_physics->AddForce(collision.overlap);
	}

	for (const auto& chip : map.GetAllMapChips())
	{
		// 移動なし当たり判定
		// 多少軽い
		CollisionStatus col = m_collider->CheckHit(chip->GetCollider());
		if (!col.isCollide) continue;

		// Environmentを記憶
		hitEnvironments.push_back(chip->GetMapChipData().environment);
	}
	// マップ外の場合は今の状態から変わらない
	if (hitEnvironments.empty()) return;

	// 自分の物理状態が一つもなかったらtrue
	bool envChanged = true;
	for (const auto& env : hitEnvironments)
	{
		envChanged &= !m_physics->CheckState(env);
	}
	if (envChanged)
	{
		if (m_physics->CheckState(MapConstants::kEnvironment::kWater))
		{
			m_physics->UseConstantForce(true);
		}
		else
		{
			m_physics->UseConstantForce(false);
		}
		m_physics->InvertState();
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

HarmFish::HarmFish(ObjectsController& cont, Player& player, Camera& camera, const Vector2& initPos, const Vector2Int& baseMapPos) :
	Enemy(cont, player, camera, initPos, baseMapPos),
	m_state(&HarmFish::Idle),
	m_stateFrameCount(0),
	m_chasePoint(0)
{
	m_physics = std::make_shared<Physics>(1.0f, 1.0f);
	m_physics->UseConstantForce(false);
	m_collider = std::make_shared<CircleCollider>(m_pos, kColRadius);
	m_hp += kInitHp;
	m_scene = std::static_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene());

	// アニメーションの初期化
	m_idleAnim   = std::make_shared<Animation>();
	m_chaseAnim  = std::make_shared<Animation>();
	m_damageAnim = std::make_shared<Animation>();
	//m_deathAnim = std::make_shared<Animation>();

	m_idleAnim  ->Init(kIdleAnimFile,   kImageSize, kIdleAnimPlaySpeed);
	m_chaseAnim ->Init(kChaseAnimFile,  kImageSize, kIdleAnimPlaySpeed);
	m_damageAnim->Init(kDamageAnimFile, kImageSize, 5);

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

	HitToMap();
	m_pos += m_physics->Update();
	m_nowAnim->Update();

	// 画面外に出たらストップ
	// 画面外にはマップチップが無く、壁を貫通する恐れがある
	if (CheckScreenOut())
	{
		m_physics->Stop();
	}
}

void HarmFish::Draw() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);

	m_nowAnim->Draw(screenPos);
#if _DEBUG
	// 追跡範囲の描画
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(sqrt(kChasePointIncreaseThreshold)), 0xffffff, false);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(sqrt(kChasePointDecreaseThreshold)), 0xffffff, false);
	m_collider->DrawColliderRange_Debug(m_camera.DrawOffset());
	DrawFormatString(0, 0, 0xffffff, "今の追尾評価値:%d\n", m_chasePoint);
#endif
}