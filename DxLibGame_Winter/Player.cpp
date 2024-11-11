#include "Player.h"
#include <DxLib.h>
#include "Input.h"
#include "Physics.h"
#include "game.h"
#include "MapSystem.h"

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
}

void Player::Update(std::shared_ptr<MapSystem> map)
{
	// 入力をとって、動く。
	Input& input = Input::GetInstance();

	Vector2 axis = input.GetInputAxis();

	// Aボタンでダッシュ
	if (input.IsPressed(PAD_INPUT_1))
	{
		axis *= 1.5f;
	}

	// 仮
	DrawFormatString(0, 90, 0xffffff, "axisX:%f,Y:%f", axis.x, axis.y);
	m_physics->AddForce(axis * 0.01f);

	// 物理のUpdateは入力などで力を算出し終わった後に実行すること。

	// ここはマップがこれ以上スクロールしないかどうかを判定して自分が移動するかどうか変えたい
	m_physics->Update();
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
