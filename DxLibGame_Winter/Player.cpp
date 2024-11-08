#include "Player.h"
#include <DxLib.h>
#include "Input.h"
#include "Physics.h"

namespace
{
	// おテスト
	int kRaduis = 10;

	constexpr float kInitPosX = 100;
	constexpr float kInitPosY = 100;
}

Player::Player() :
	m_physics(std::make_shared<Physics>(Vector2(kInitPosX, kInitPosY), 1.0f))
{
}

void Player::Update()
{
	// 入力をとって、動く。
	Input& input = Input::GetInstance();

	Vector2 axis = input.GetInputAxis();
	DrawFormatString(0, 90, 0xffffff, "axisX:%f,Y:%f", axis.x, axis.y);
	m_physics->AddForce(axis * 0.1f);

	// 物理のUpdateは入力などで力を算出し終わった後に実行すること。
	m_physics->Update();
}

void Player::Draw()
{
	// Physicsインスタンスから座標をコピーしてくる
	Vector2 copyPos = m_physics->GetPos();
	DrawCircle(copyPos.x, copyPos.y, 10, 0xff0000);
#if _DEBUG
	DrawFormatString(0, 15, 0xffffff, "PlayerPos:x = %f, y = %f", copyPos.x, copyPos.y);
#endif
}
