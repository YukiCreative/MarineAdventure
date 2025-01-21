#include "Enemy.h"
#include "Camera.h"
#include "Vector2.h"
#include "game.h"
#include "MapConstants.h"
#include "ObjectsController.h"

namespace
{
	// ��ʊO�ɂłď�����Ƃ��A
	// �}�b�v�ɍ��킹�Ȃ��ƕ����o��Ǝv���̂�
	constexpr int kOffset = 40;
}

Enemy::Enemy(ObjectsController& cont, Player& player, Camera& camera, const Vector2& spawnPos, const Vector2Int& baseMapPos) :
	GameObject(spawnPos, baseMapPos),
	m_camera(camera),
	m_hp(0),
	m_playerRef(player),
	// ���̕ӂ͔h���N���X���œ���Ă��炨������
	m_physics(nullptr),
	m_cont(cont)
{
}

bool Enemy::CheckScreenOut() const
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	// ��ʂ̊O�ɏo����
	if (screenPos.x > Game::kScreenWidth + kOffset)		return true;
	if (screenPos.x < -kOffset)							return true;
	if (screenPos.y > Game::kScreenHeight + kOffset)	return true;
	if (screenPos.y < -kOffset)							return true;

	return false;
}
