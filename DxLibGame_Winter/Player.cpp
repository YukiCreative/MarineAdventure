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

namespace
{
	// おテスト
	int kRaduis = 20;
	// Axisがでかすぎるんだよ
	constexpr float kMoveForceFactor = 0.0002f;
	constexpr float kDashForceFactor = 0.0003f;
	constexpr float kStrongAttackForceFactor = 0.0001f;
	constexpr int kAttackFrame = 60;
	constexpr int kInvincibleFrame = 90;
	constexpr int kStrongAttackForce = 30;
}

// 何も操作されていない状態。
void Player::Normal(Input& input, Vector2& axis)
{
	// Bボタンでアタック状態
	if (input.IsTrigger(PAD_INPUT_2))
	{
		m_graphic = "A";
		m_state = &Player::Attack;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// スティックでMoveへ
	if (axis.SqrMagnitude() > 10000)
	{
		m_graphic = "M";
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
	if (input.IsPressed(PAD_INPUT_1))
	{
		m_graphic = "D";
		m_state = &Player::Dash;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// 入力がなかったらNomalへ
	if (axis.SqrMagnitude() < 10000)
	{
		m_graphic = "N";
		m_state = &Player::Normal;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// Bボタンでアタック状態
	if (input.IsTrigger(PAD_INPUT_2))
	{
		m_graphic = "SA";
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
	if (!input.IsPressed(PAD_INPUT_1))
	{
		m_graphic = "M";
		m_state = &Player::Move;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// Bボタンでアタック状態
	if (input.IsTrigger(PAD_INPUT_2))
	{
		m_graphic = "SA";
		// ここで力を加える
		m_physics->AddForce(axis.GetNormalize() * kStrongAttackForce);
		m_state = &Player::StrongAttack;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// 	// 入力がなかったらNomalへ
	if (axis.SqrMagnitude() < 10000)
	{
		m_graphic = "N";
		m_state = &Player::Normal;
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
		m_stateFrameCount = 0;
		m_graphic = "N";
		m_state = &Player::Normal;
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
		m_stateFrameCount = 0;
		m_graphic = "N";
		m_state = &Player::Normal;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
	// 攻撃判定を持つ
	// ちょっと移動ができる
	m_physics->AddForce(axis * kStrongAttackForceFactor);
}

void Player::Damage(Input& input, Vector2& axis)
{
	// ダメージを受けたらこの状態へ
	// 一定時間無敵
	++m_stateFrameCount;
	if (m_stateFrameCount >= kInvincibleFrame)
	{
		m_stateFrameCount = 0;
		m_graphic = "N";
		m_state = &Player::Normal;
		(this->*m_state)(input, axis); // 次の状態の内容を実行
		return;
	}
}

void Player::Death(Input& input, Vector2& axis)
{
	// 死亡モーション
	// 別のシーンへ
}

Player::Player(std::shared_ptr<Camera> camera) :
	m_physics(std::make_shared<Physics>(1.0f, 1.0f)),
	m_state(&Player::Normal),
	m_graphic("N"),
	m_stateFrameCount(0),
	m_hp(0)
{
	m_collider = std::make_shared<CircleCollider>(m_pos, kRaduis);
	m_camera = camera;
}

void Player::Update(std::shared_ptr<MapSystem> map)
{
	// 入力とる
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	// 現在の状態の処理
	(this->*m_state)(input, axis);

	// 物理のUpdateは入力などで力を算出し終わった後に実行すること。
	Vector2 vel = m_physics->Update();

	// 当たり判定の処理
	// マップチップ一つ一つと判定する
	for (auto& chip : map->GetMapCihps())
	{
		if (m_collider->CheckHit(chip->GetCollider()))
		{
			// マップチップの種類を見たいよね
			// 特定のマップチップと当たっていたら、今フレームの移動量をいじりたい
			// これポリった方が良くね
			// マップチップにプレイヤーと当たった時の振る舞いを覚えてもらって
			// チップの関数を実行
			// チップがプレイヤーの移動量をいじるのはどうなのか
			// 壁や水流によってプレイヤーの移動が阻害されていると考えればむしろ自然か
		}
	}

	// 最後に移動
	m_pos += vel;
}

void Player::Draw() const
{
	Vector2 screenPos = m_camera->Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), kRaduis, 0xff0000);
	DrawString(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), m_graphic.c_str(), 0x000000);
#if _DEBUG
	DrawFormatString(0, 15, 0x000000, "PlayerPos:x = %f, y = %f", m_pos.x, m_pos.y);
	DrawFormatString(0, 105, 0x000000, "screenPos:x = %f, y = %f", screenPos.x, screenPos.y);
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();
	DrawFormatString(0, 30, 0x000000, "InputAxis x:%f,y:%f", axis.x, axis.y);
#endif
}

Vector2 Player::GetVel() const
{
	return m_physics->GetVel();
}
