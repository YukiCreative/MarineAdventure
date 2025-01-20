#pragma once
#include "GameObject.h"
#include <memory>
#include "HitPoint.h"

class Camera;
class Physics;
class Player;

/// <summary>
/// 敵の基底クラス
/// </summary>
class Enemy : public GameObject
{
protected:
	Camera& m_camera;
	HitPoint m_hp;
	std::shared_ptr<Physics> m_physics;
	Player& m_playerRef;

	Vector2Int m_baseMapPos;
public:
	Enemy(Player& player, Camera& camera, Vector2 spawnPos);
	~Enemy();

	/// <summary>
	/// スクリーンの外かどうか
	/// </summary>
	bool CheckScreenOut() const;
};