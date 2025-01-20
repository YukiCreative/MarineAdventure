#include "Enemy.h"
#include "Camera.h"
#include "Vector2.h"
#include "game.h"
#include "MapConstants.h"

namespace
{
	// 画面外にでて消えるとき、
	// マップに合わせないと複数出ると思うので
	constexpr int kOffset = 40;
}

Enemy::Enemy(Player& player, Camera& camera, Vector2 spawnPos) :
	GameObject(spawnPos),
	m_camera(camera),
	m_hp(0),
	m_playerRef(player),
	// この辺は派生クラス側で入れてもらおうかな
	m_physics(nullptr),
	m_baseMapPos(spawnPos.x / MapConstants::kChipSize, spawnPos.y / MapConstants::kChipSize)
{
}

Enemy::~Enemy()
{
	// 

}

bool Enemy::CheckScreenOut() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	// 画面の外に出たら
	if (screenPos.x > Game::kScreenWidth + kOffset)		return true;
	if (screenPos.x < -kOffset)							return true;
	if (screenPos.y > Game::kScreenHeight + kOffset)	return true;
	if (screenPos.y < -kOffset)							return true;

	return false;
}
