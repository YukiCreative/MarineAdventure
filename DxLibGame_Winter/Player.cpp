#include "Player.h"
#include <DxLib.h>
#include "Input.h"

namespace
{
	// おテスト
	int kRaduis = 10;
}

Player::Player() :
	m_pos(100, 100)
{
}

void Player::Update()
{
	// 入力をとって、動く。
	Input& input = Input::GetInstance();

	if (input.IsPressed(PAD_INPUT_1))
	{

	}
}

void Player::Draw()
{
	DrawCircle(m_pos.x, m_pos.y, 10, 0xff0000);
}
