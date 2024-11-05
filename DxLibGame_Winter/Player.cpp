#include "Player.h"
#include <DxLib.h>

namespace
{
	// ‚¨ƒeƒXƒg
	int kRaduis = 10;
}

Player::Player() :
	m_pos(100, 100)
{
}

void Player::Update()
{
	++m_pos.x;
}

void Player::Draw()
{
	DrawCircle(m_pos.x, m_pos.y, 10, 0xff0000);
}
