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
	constexpr int kMoveThreshold = 10000;
	const Vector2 kJumpForce(0.0f, -10.0f);
	const Vector2Int kPlayerGraphSize(32, 32);

	const std::string kIdleAnimPath = "Idle (32x32).png";
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
	if (axis.SqrMagnitude() > kMoveThreshold)
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
	if (axis.SqrMagnitude() < kMoveThreshold)
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
	if (axis.SqrMagnitude() < kMoveThreshold)
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

void Player::GNormal(Input& input, Vector2& axis)
{
	// いろいろなモーションにつながる
	if (input.IsPressed("Jump"))
	{
		m_physics->AddForce(kJumpForce);
		m_state = &Player::Jump;
		(this->*m_state)(input, axis);
		return;
	}
}

void Player::GMove(Input& input, Vector2& axis)
{
	if (input.IsTrigger("Jump"))
	{
		m_physics->AddForce(kJumpForce);
		m_graphic = "Jump";
		m_state = &Player::Jump;
		(this->*m_state)(input, axis);
		return;
	}
	if (axis.SqrMagnitude() < kMoveThreshold)
	{
		m_graphic = "GN";
		m_state = &Player::GNormal;
		(this->*m_state)(input, axis);
		return;
	}
}

void Player::GDash(Input& input, Vector2& axis)
{
	// 腹滑りでもする？ペンギンだし
}

void Player::Jump(Input& input, Vector2& axis)
{
	// 空中モーション
	// 左右に動ける
	Vector2 sideAxis = Vector2(axis.x, 0.0f);
	m_physics->AddForce(sideAxis * kMoveForceFactor);
	// ジャンプの遷移は存在しないので、多段ジャンプしない
	// 着地したらGNormalへ
	// 着水は網羅できている
}

void Player::SetStateNormal()
{
	// 状態遷移する処理が重複していたので
	m_stateFrameCount = 0;
	m_graphic = "N";
	m_physics->UseConstantForce(true);
	m_state = &Player::Normal;
}

bool Player::CheckEnvironmentChanged()
{
	// もう一回当たり判定する
	// すべてのマップチップが対象
	const auto& allMapChips = m_map.lock()->GetAllMapChips();
	std::list<MapConstants::Environment> hitEnvironments;
	for (const auto& chip : allMapChips)
	{
		// 移動なし当たり判定
		// 多少軽い
		CollisionStatus col = m_collider->CheckHit(chip->GetCollider());
		if (!col.isCollide) continue;

		// Environmentを記憶
		hitEnvironments.push_back(chip->GetMapChipData().environment);
	}
	// 自分の物理状態が一つもなかったらtrue
	bool result = true;
	for (const auto& env : hitEnvironments)
	{
		result &= !m_physics->CheckState(env);
	}
	return result;
}

void Player::CollideToMapChips()
{
	// マップとの衝突処理を分けた
	// ここでマップの壁との当たり判定
	m_contactAngles.clear();
	auto& collidableMapChips = m_map.lock()->GetCollidableMapChips();
	Vector2 pushBackVec = Vector2::Zero();
	for (const auto& chip : collidableMapChips)
	{
		CollisionStatus col = m_collider->CheckHit(chip->GetCollider(), m_velocity);
		if (!col.isCollide) continue;

		// 色を変えてみる
		//chip->ChangeGraph_Debug();

		// 壁に吸い付くような挙動になって違和感があるので力を加える
		Vector2 overlapN = col.overlap.GetNormalize();
		// 現在の速度の分、当たっている壁の向きだけ力を加える
		Vector2 addforce(m_velocity.x * std::abs(overlapN.x), m_velocity.y * std::abs(overlapN.y));
		m_physics->AddForce(-addforce * kBounceFactor);

		// 接触した面の角度を取得
		//m_contactAngles.push_back();

		m_velocity -= col.overlap;
	}
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
	m_idleAnim->Init(kIdleAnimPath, kPlayerGraphSize, 2);
	m_nowAnim = m_idleAnim;
}

Player::~Player()
{
}

void Player::Update()
{
	// 速度クリア
	m_velocity = Vector2::Zero();

	// 入力とる
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	// 現在の状態の処理
	(this->*m_state)(input, axis);

	// 物理のUpdateは入力などで力を算出し終わった後に実行すること。
	m_velocity = m_physics->Update();

	CollideToMapChips();

	// 物理状態の遷移
	// これ各状態に設置した方が分岐減るのでは
	if (CheckEnvironmentChanged())
	{
		// 地上→水中
		if (m_physics->CheckState(MapConstants::Environment::kGround))
		{
			m_physics->ChangeState(MapConstants::Environment::kWater);
			m_graphic = "N";
			m_physics->UseConstantForce(true);
			m_state = &Player::Normal;
		}
		// 水中→地上
		else
		{
			m_physics->ChangeState(MapConstants::Environment::kGround);
			m_graphic = "Jump";
			m_physics->UseConstantForce(true);
			if (input.IsPressed("Dash"))
			{
				m_physics->AddForce(kJumpForce);
			}
			m_state = &Player::Jump;
		}
	}

	// 最後に移動
	m_pos += m_velocity;

	m_nowAnim->Update();
}

void Player::Draw() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), static_cast<int>(kRaduis), 0xff0000);
	m_nowAnim->Draw(screenPos);
#if _DEBUG
	DrawFormatString(0, 15, 0x999999, "PlayerPos:x = %f, y = %f", m_pos.x, m_pos.y);
	DrawFormatString(0, 105, 0x999999, "screenPos:x = %f, y = %f", screenPos.x, screenPos.y);
	DrawFormatString(0, 120, 0x999999, "vel:x = %f, y = %f", m_velocity.x, m_velocity.y);
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