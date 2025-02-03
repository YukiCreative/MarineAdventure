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
	// プレイヤーの当たり判定に使います
	constexpr float kColliderRaduis = 30.0f;
	constexpr int   kMaxHp = 5;
	// Axisがでかすぎるんだよ
	constexpr float  kMoveForceFactor = 0.0002f;
	constexpr float  kJumpingMoveForceFactor = 0.0001f;
	constexpr float  kDashForceFactor = 0.0003f;
	constexpr float  kStrongAttackMoveFactor = 0.0001f;
	constexpr float  kDuringDamageMoveFactor = 0.0001f;

	constexpr float  kAttackFrame = 60.0f;
	constexpr float  kInvincibleFrame = 90.0f;
	constexpr float  kAttackedRigidFrame = 30.0f;
	constexpr int    kDeathRigidFrame = 120; // 死後硬直
	constexpr int    kDeathDisappearFrame = 60; // 爆散
	constexpr float  kStrongAttackForce = 20.0f;
	constexpr float  kBounceFactor = 1.2f;
	constexpr int    kMoveThreshold = 10000;
	constexpr int	 kGroundMoveThreshold = 100;

	const Vector2    kJumpForce      = { 0.0f, -15.0f };
	const Vector2    kWaterJumpForce = { 0.0f, -7.0f  };
	const Vector2    kDashJumpForce  = { 0.0f, -20.0f };
	constexpr float  kFallThreshold  = 2.0f;
	// 着地できる地面の角度(法線)
	constexpr int kLandingThresholdMin = 45;
	constexpr int kLandingThresholdMax = 135;
	// アニメーション
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

	// 音のファイル
	const std::string kIntoWaterSound  = "IntoTheWater.wav";
	const std::string kOutOfWaterSound = "水音　バシャ.mp3";
	const std::string kStunSound       = "Stun.wav";
	const std::string kAttackSound     = "レトロアクション.mp3";
	const std::string kWalkSound1      = "スライム的な.mp3";
	const std::string kWalkSound2      = "スライム的な_2.mp3";
	const std::string kDeathSound      = "自機ロスト音.mp3";
	constexpr     int kWalkSoundSpan   = 20;
	constexpr     int kDashSoundSpan   = 10;

	// エフェクト
	// こんなに必要な変数が多いならクラス化した方がいい気がする
	const std::string kDashEffectFile = "PlayerDashEffect.png";
	const Vector2Int kDashEffectImageSize = { 32, 32 };
	const Vector2 kLeftDashEffectOffset = { -20, 16 };
	const Vector2 kRightDashEffectOffset = { 20, 16 };
}

void Player::GameOver()
{
	std::shared_ptr<SceneGame> gameScene = std::dynamic_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "ゲームシーンに動的キャストできなかった");
	gameScene->GameOver();
}

// 何も操作されていない状態。
void Player::Normal(Input& input, Vector2& axis)
{
	// Bボタンでアタック状態
	if (input.IsTrigger("Attack"))
	{
		m_stateText = "A";
		SetStateAttack();
		return;
	}
	// スティックでMoveへ
	if (axis.SqrMagnitude() > kMoveThreshold)
	{
		m_stateText = "M";
		m_physics->UseConstantForce(false);
		ChangeState(&Player::Move);
		return;
	}
	// 速度に応じて向きを変える
	ChangeRotation();
}

// 移動してます
void Player::Move(Input& input, Vector2& axis)
{
	// ダッシュ押されてたらDashへ
	if (input.IsPressed("Dash"))
	{
		m_stateText = "D";
		m_physics->UseConstantForce(false);
		ChangeState(&Player::Dash);
		 // 次の状態の内容を実行
		return;
	}
	// 入力がなかったらNomalへ
	if (axis.SqrMagnitude() < kMoveThreshold)
	{
		SetStateNormal();
		return;
	}
	// Bボタンでアタック状態
	if (input.IsTrigger("Attack"))
	{
		m_stateText = "SA";
		// ここで力を加える
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		SetStateAttack();
		return;
	}
	// 仮
	m_physics->AddForce(axis * kMoveForceFactor);
	// 現在の移動方向によってモーションを変える
	ChangeDirection(axis);
	// 速度に応じて向きを変える
	ChangeRotation();
}

// 早いです。
void Player::Dash(Input& input, Vector2& axis)
{
	// ダッシュ押されてなかったらMoveへ
	if (!input.IsPressed("Dash"))
	{
		m_stateText = "M";
		m_physics->UseConstantForce(false);
		ChangeState(&Player::Move);
		 // 次の状態の内容を実行
		return;
	}
	// Bボタンでアタック状態
	if (input.IsTrigger("Attack"))
	{
		m_stateText = "SA";
		// ここで力を加える
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		SetStateAttack();
		return;
	}
	// 	// 入力がなかったらNomalへ
	if (axis.SqrMagnitude() < kMoveThreshold)
	{
		SetStateNormal();
		return;
	}
	// 仮
	m_physics->AddForce(axis * kDashForceFactor);
	// モーションが変わるのはこちらも同じ
	ChangeDirection(axis);
	// 速度に応じて向きを変える
	ChangeRotation();
}

void Player::Attack(Input& input, Vector2& axis)
{
	// 攻撃判定を持つ
	// 一定時間経ったらNormalへ
	if (m_stateFrameCount >= kAttackFrame)
	{
		SetStateNormal();
		ChangeAnimation(m_idleAnim);
		return;
	}
	// 移動ができる
	m_physics->AddForce(axis * kMoveForceFactor);
}

void Player::StrongAttack(Input& input, Vector2& axis)
{
	// 一定時間経ったらNormalへ
	if (m_stateFrameCount >= kAttackFrame)
	{
		SetStateNormal();
		return;
	}
	// 攻撃判定を持つ
	// ちょっと移動ができる
	m_physics->AddForce(axis * kStrongAttackMoveFactor);
}

void Player::Damage(Input& input, Vector2& axis)
{
	// ダメージを受けたらこの状態へ
	// 一定時間無敵
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
	// 01/14　動けるように
	m_physics->AddForce(axis * kDuringDamageMoveFactor);
}

void Player::Death(Input& input, Vector2& axis)
{
	// 死亡モーション
	if (m_stateFrameCount > kDeathRigidFrame)
	{
		m_nowAnim = m_deathAnim;
		SoundManager::GetInstance().Play(kDeathSound);
		ChangeState(&Player::DisAppear);
	}
}

void Player::DisAppear(Input& input, Vector2& axis)
{
	// 終わったら別のシーンへ
	if (m_stateFrameCount > kDeathDisappearFrame)
	{
		GameOver();
	}
}

void Player::Attacked(Input& input, Vector2& axis)
{
	// 硬直なのでモーション以外何もしない
	if (m_stateFrameCount >= kAttackedRigidFrame)
	{
		SetStateNormal();
		return;
	}
}

void Player::GNormal(Input& input, Vector2& axis)
{
	// いろいろなモーションにつながる
	if (input.IsTrigger("Jump"))
	{
		m_physics->AddForce(kJumpForce);
		SoundManager::GetInstance().Play("ファニージャンプ_2.mp3");
		SetStateJump();
		return;
	}
	if (m_velocity.y > kFallThreshold)
	{
		// ジャンプなし空中状態
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
	// キャラの向きを変える
	ChangeDirection(axis);
	if (input.IsTrigger("Jump"))
	{
		m_physics->AddForce(kJumpForce);
		SoundManager::GetInstance().Play("ファニージャンプ_2.mp3");
		SetStateJump();
		return;
	}
	if (m_velocity.y > kFallThreshold)
	{
		// ジャンプなし空中状態
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
		// 元データが左向きなんですよ
		effect->ReverceX(!m_isLeft);
		effect->SetExRate(2.0f);
		ChangeAnimation(m_dashAnim);
		return;
	}
	// こいつ動くぞ
	m_physics->AddForce(axis.x * kMoveForceFactor);
	// 一定時間ごとに足音を鳴らす
	if (!(m_stateFrameCount % kWalkSoundSpan)) PlayWalkSound();
}

void Player::GDash(Input& input, Vector2& axis)
{
	// 入力がなくなったら通常移動へ
	if (!input.IsPressed("Dash"))
	{
		m_stateText = "GN";
		ChangeState(&Player::GMove);
		ChangeAnimation(m_walkAnim);
		return;
	}
	// 入力がなくなったら通常状態へ
	if (abs(axis.x) < kGroundMoveThreshold)
	{
		m_stateText = "GN";
		ChangeState(&Player::GNormal);
		ChangeAnimation(m_idleAnim);
		return;
	}
	if (input.IsTrigger("Jump"))
	{
		// ダッシュジャンプはちょっと高く飛びたい
		m_physics->AddForce(kDashJumpForce);
		SoundManager::GetInstance().Play("ファニージャンプ_3.mp3");
		SetStateJump();
		return;
	}
	if (m_velocity.y > kFallThreshold)
	{
		SetStateJump();
		// アニメーションの切り替えが重複しているのが気になる
		m_nowAnim = m_fallAnim;
		return;
	}
	// 早く動ける
	m_physics->AddForce(axis.x * kDashForceFactor);
	// キャラの向きを変える
	ChangeDirection(axis);
	// 一定時間ごとに足音を鳴らす
	if (!(m_stateFrameCount % kDashSoundSpan)) PlayWalkSound();
}

void Player::Air(Input& input, Vector2& axis)
{
	// 空中モーション
	// 左右に動ける
	Vector2 sideAxis = Vector2(axis.x, 0.0f);
	// 着地したらGNormalへ
	for (const auto& overlap : m_overlaps)
	{
		float angle = overlap.Angle();
		// continue見づらいかなあ
		if (angle < kLandingThresholdMin || angle > kLandingThresholdMax) continue;

		m_stateText = "GN";
		m_physics->IsGrounded(true);
		ChangeState(&Player::GNormal);
		ChangeAnimation(m_idleAnim);
		// 立ちモーションが斜めっている場合があるので向きリセット
		m_nowAnim->SetRotate(0);
		return;
	}
	m_physics->AddForce(sideAxis * kJumpingMoveForceFactor);
	ChangeDirection(axis);
	ChangeFallAnim();
}

void Player::SetStateNormal()
{
	// 状態遷移する処理が重複していたので
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
	// もう一回当たり判定する
	// すべてのマップチップが対象
	const auto& allMapChips = m_map.lock()->GetAllMapChips();
	std::list<MapConstants::kEnvironment> hitEnvironments;
	for (const auto& chip : allMapChips)
	{
		// 移動なし当たり判定
		// 多少軽い
		CollisionStatus col = m_collider->CheckHit(chip->GetCollider());
		if (!col.isCollide) continue;

		// Environmentを記憶
		hitEnvironments.push_back(chip->GetMapChipData().environment);
	}
	// マップ外の場合は今の状態から変わらない
	if (hitEnvironments.empty()) return false;

	// 自分が水中にいる場合、
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

	// マップとの衝突処理を分けた
	auto& collidableMapChips = m_map.lock()->GetCollidableMapChips();
	Vector2 pushBackVec = Vector2::Zero();
	for (const auto& chip : collidableMapChips)
	{
		CollisionStatus col = m_collider->CheckHit(chip->GetCollider(), m_velocity);
		if (!col.isCollide) continue;

		// 色を変えてみる
		//chip->ChangeGraph_Debug();

		// めり込みを記録
		m_overlaps.push_back(col.overlap);
		overlapSum += col.overlap;
	}

	// 壁に吸い付くような挙動になって違和感があるので力を加える
	// 角に当たった時は無効にしたい
	Vector2 overlapN = overlapSum.GetNormalize();
	// 現在の速度の分、当たっている壁の向きだけ力を加える
	Vector2 addforce(m_velocity.x * std::abs(overlapN.x), m_velocity.y * std::abs(overlapN.y));
	m_physics->AddForce(-addforce * kBounceFactor);

	// 最後に反映
	m_velocity -= overlapSum;
}

void Player::ChangeState(StateFunc_t nextState)
{
	m_stateFrameCount = 0;
	m_state = nextState;
	// ステートの実行はしない
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
	// 今の移動方向に応じて向きを変えたい
	m_nowAnim->ReverceX(m_velocity.x < 0);
}

void Player::PlayWalkSound()
{
	// ピッチをランダムにしたかった
	SoundManager::GetInstance().Play(GetRand(1) ? kWalkSound1 : kWalkSound2);
}

void Player::ChangeRotation()
{
	// 速度に応じて向きを変える
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
	// ここからアニメーションの初期化
	// これってまとめたほうがいいのか都度宣言して初期化関数流したほうがいいのか
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
	// 入力とる
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();

	++m_stateFrameCount;
	// 現在の状態の処理
	(this->*m_state)(input, axis);

	// 速度クリア
	m_velocity = Vector2::Zero();

	// 物理のUpdateは入力などで力を算出し終わった後に実行すること。
	m_velocity = m_physics->Update();

	CollideToMapChips();

	// 物理状態の遷移
	// これ各状態に設置した方が分岐減るのでは
	if (CheckEnvironmentChanged())
	{
		// 地上→水中
		if (m_physics->CheckState(MapConstants::kEnvironment::kGround))
		{
			// いろいろやってんなあ
			m_physics->IsGrounded(false);
			m_physics->ChangeState(MapConstants::kEnvironment::kWater);
			SetStateNormal();
			SoundManager::GetInstance().Play(kIntoWaterSound);
			// 水の衝撃でスピードが落ちる感じ
			m_physics->AddForce(-m_velocity * 0.5f);
		}
		// 水中→地上
		else
		{
			m_physics->ChangeState(MapConstants::kEnvironment::kGround);
			m_physics->UseConstantForce(true);
			if (CheckState(PlayerState::kDash)) { m_physics->AddForce(kWaterJumpForce); }
			SetStateJump();
			SoundManager::GetInstance().Play(kOutOfWaterSound);
		}
	}

	// 最後に移動
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
	// 操作を受け付けず、アニメーションだけを更新
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
	// 列挙体とswitch文を撲滅したい　あー
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
	// ダメージ状態なら食らわない
	if (CheckState(PlayerState::kDamage)) return;

	// こんなのでいいんでしょうか
	m_hp -= damage;
#if _DEBUG
	printf("Playerの体力%d\n", m_hp.Value());
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
	// 攻撃時モーションに切り替え
	ChangeState(&Player::Attacked);
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	m_stateText = "やったぜ。";
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
