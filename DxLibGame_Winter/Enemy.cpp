#include "Enemy.h"
#include "Camera.h"
#include "Vector2.h"
#include "game.h"
#include "EnemyController.h"

namespace
{
	// 画面外にでて消えるとき、
	// マップに合わせないと複数出ると思うので
	constexpr int kOffset = 40;
}

Enemy::Enemy(Player& player, Camera& camera, EnemyController& controller, Vector2 spawnPos) :
	GameObject(spawnPos),
	m_camera(camera),
	m_hp(0),
	m_playerRef(player),
	m_controller(controller),
	// この辺は派生クラス側で入れてもらおうかな
	m_physics(nullptr),
	m_isDead(false)
{
}

bool Enemy::CheckScreenOut()
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	// 画面の外に出たら
	if (screenPos.x > Game::kScreenWidth + kOffset)		return true;
	if (screenPos.x < -kOffset)							return true;
	if (screenPos.y > Game::kScreenHeight + kOffset)	return true;
	if (screenPos.y < -kOffset)							return true;

	return false;
}
