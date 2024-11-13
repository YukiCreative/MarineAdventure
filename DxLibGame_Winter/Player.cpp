#include "Player.h"
#include <DxLib.h>
#include "Input.h"
#include "Physics.h"
#include "game.h"
#include "MapSystem.h"
#include "CircleCollider.h"
#include "MapChip.h"

namespace
{
	// おテスト
	int kRaduis = 20;

	constexpr float kInitPosX = Game::kScreenWidth * 0.5f;
	constexpr float kInitPosY = Game::kScreenHeight * 0.5f;
}

Player::Player() :
	m_physics(std::make_shared<Physics>(1.0f, 1.0f)),
	m_pos(kInitPosX, kInitPosY)
{
	m_collider = std::make_shared<CircleCollider>(m_pos, kRaduis);
}

void Player::Update(std::shared_ptr<MapSystem> map)
{
	// 入力をとって、動く。
	Input& input = Input::GetInstance();

	Vector2 axis = input.GetInputAxis();

	// Aボタンでダッシュ状態へ(今後はアタックと同時にできないように)
	if (input.IsPressed(PAD_INPUT_1))
	{
		axis *= 1.5f;
	}
	// 仮
	m_physics->AddForce(axis * 0.01f);
	// Bボタンでアタック状態
	if (input.IsTrigger(PAD_INPUT_2))
	{
		m_physics->Stop();
		m_physics->AddForce(axis);
	}

	// 当たり判定の処理
	// マップチップ一つ一つと判定する
	for (auto& chip : map->GetMapCihps())
	{
		if (m_collider->CheckHit(chip->Collider()))
		{
			// これは仮で、後でprivateに戻す
			chip->SetGraph();
		}
	}

	// 物理のUpdateは入力などで力を算出し終わった後に実行すること。

	// ここはマップがこれ以上スクロールしないかどうかを判定して自分が移動するかどうか変えたい
	m_physics->Update();
	//if (スクロールできない)
	//{
	//	m_pos += m_physics->GetVel();
	//}
}

void Player::Draw()
{
	DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), kRaduis, 0xff0000);
#if _DEBUG
	DrawFormatString(0, 15, 0x000000, "PlayerPos:x = %f, y = %f", m_pos.x, m_pos.y);
#endif
}

Vector2 Player::GetVel()
{
	return m_physics->GetVel();
}
