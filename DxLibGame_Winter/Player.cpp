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
	// プレイヤーの当たり判定に使います
	constexpr float kRaduis = 20.0f;
	constexpr int kMaxHp = 5;
	// Axisがでかすぎるんだよ
	constexpr float kMoveForceFactor = 0.0002f;
	constexpr float kDashForceFactor = 0.0003f;
	constexpr float kStrongAttackMoveFactor = 0.0001f;
	constexpr float kAttackFrame = 60.0f;
	constexpr float kInvincibleFrame = 90.0f;
	constexpr float kAttackedRigidFrame = 30.0f;
	constexpr float kStrongAttackForce = 20.0f;
	constexpr float kBounceFactor = 1.2f;

	const Vector2Int kPlayerGraphSize(32, 32);
}

// 何も操作されていない状態。
void Player::Normal(Input& input, Vector2& axis)
{
	// Bボタンでアタック状態
	if (input.IsTrigger("Attack"))
	{
		m_graphic = "A";
		m_physics->UseConstantForce(false);
		m_state = &Player::Attack;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// スティックでMoveへ
	if (axis.SqrMagnitude() > 10000)
	{
		m_graphic = "M";
		m_physics->UseConstantForce(false);
		m_state = &Player::Move;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// 現在の移動方向によってモーションを変える
}

// 移動してます
void Player::Move(Input& input, Vector2& axis)
{
	// ダッシュ押されてたらDashへ
	if (input.IsPressed("Dash"))
	{
		m_graphic = "D";
		m_physics->UseConstantForce(false);
		m_state = &Player::Dash;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// 入力がなかったらNomalへ
	if (axis.SqrMagnitude() < 10000)
	{
		SetStateNormal();
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// Bボタンでアタック状態
	if (input.IsTrigger("Attack"))
	{
		m_graphic = "SA";
		m_physics->UseConstantForce(false);
		// ここで力を加える
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		m_state = &Player::StrongAttack;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// 仮
	m_physics->AddForce(axis * kMoveForceFactor);
	// 現在の移動方向によってモーションを変える
}

// 早いです。
void Player::Dash(Input& input, Vector2& axis)
{
	// ダッシュ押されてなかったらMoveへ
	if (!input.IsPressed("Dash"))
	{
		m_graphic = "M";
		m_physics->UseConstantForce(false);
		m_state = &Player::Move;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// Bボタンでアタック状態
	if (input.IsTrigger("Attack"))
	{
		m_graphic = "SA";
		m_physics->UseConstantForce(false);
		// ここで力を加える
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		m_state = &Player::StrongAttack;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// 	// 入力がなかったらNomalへ
	if (axis.SqrMagnitude() < 10000)
	{
		SetStateNormal();
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// 仮
	m_physics->AddForce(axis * kDashForceFactor);
	// モーションが変わるのはこちらも同じ
}

void Player::Attack(Input& input, Vector2& axis)
{
	// 攻撃判定を持つ
	// 一定時間経ったらNormalへ
	++m_stateFrameCount;
	if (m_stateFrameCount >= kAttackFrame)
	{
		SetStateNormal();
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// 移動ができる
	m_physics->AddForce(axis * kMoveForceFactor);
}

void Player::StrongAttack(Input& input, Vector2& axis)
{
	// 一定時間経ったらNormalへ
	++m_stateFrameCount;
	if (m_stateFrameCount >= kAttackFrame)
	{
		SetStateNormal();
		(this->*m_state)(input, axis); // 次の状態の内容を実行
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
	++m_stateFrameCount;
	if (m_stateFrameCount >= kInvincibleFrame)
	{
		SetStateNormal();
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}

}

void Player::Death(Input& input, Vector2& axis)
{
	// 死亡モーション
	// 別のシーンへ
	// こいつが生きているかどうかをシーンが毎フレームチェック
	m_isDeleted = true;
}

void Player::Attacked(Input& input, Vector2& axis)
{
	// 硬直なのでモーション以外何もしない
	++m_stateFrameCount;
	if (m_stateFrameCount >= kAttackedRigidFrame)
	{
		SetStateNormal();
		(this->*m_state)(input, axis);
		return;
	}
}

void Player::SetStateNormal()
{
	// 状態遷移する処理が重複していたので
	m_stateFrameCount = 0;
	m_graphic = "N";
	m_physics->UseConstantForce(true);
	m_state = &Player::Normal;
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
	// ここからアニメーションの初期化
	m_idleAnim = std::make_shared<Animation>();
	m_idleAnim->Init("Data/Image/Idle (32x32).png", kPlayerGraphSize, 2);
	m_nowAnim = m_idleAnim;
}

Player::~Player()
{
}

void Player::Update()
{
	// 入力とる
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	// 現在の状態の処理
	(this->*m_state)(input, axis);

	// 物理のUpdateは入力などで力を算出し終わった後に実行すること。
	Vector2 vel = m_physics->Update();

	// ここでマップの壁との当たり判定
	auto& collidableMapChips = m_map.lock()->GetCollidableMapChips();
	for (const auto& chip : collidableMapChips)
	{
		CollisionStatus col = m_collider->CheckHit(chip->GetCollider(), vel);
		if (!col.isCollide) continue;

		// 色を変えてみる
		//chip->ChangeGraph_Debug();

		// 壁に吸い付くような挙動になって違和感があるので力を加える
		Vector2 overlapN = col.overlap.GetNormalize();
		// 現在の速度の分、当たっている壁の向きだけ力を加える
		Vector2 addforce(vel.x * std::abs(overlapN.x), vel.y * std::abs(overlapN.y));
		m_physics->AddForce(-addforce * kBounceFactor);

		vel -= col.overlap;
	}

	// 最後に移動
	m_pos += vel;

	m_nowAnim->Update();
}

void Player::Draw() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(kRaduis), 0xff0000);
	m_nowAnim->Draw(screenPos);
#if _DEBUG
	DrawFormatString(0, 15, 0xffffff, "PlayerPos:x = %f, y = %f", m_pos.x, m_pos.y);
	DrawFormatString(0, 105, 0xffffff, "screenPos:x = %f, y = %f", screenPos.x, screenPos.y);
	DrawString(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), m_graphic.c_str(), 0x00ff00);
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
	printf("Playerの体力%d\n", m_hp);
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
	// 攻撃時モーションに切り替え
	m_stateFrameCount = 0;
	m_state = &Player::Attacked;
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	m_graphic = "やったぜ。";
	(this->*m_state)(input, axis);
	return;
}