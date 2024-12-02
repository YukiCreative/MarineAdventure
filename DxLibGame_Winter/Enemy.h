#pragma once
#include "GameObject.h"
#include <memory>

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
	int m_hp;
	std::shared_ptr<Physics> m_physics;
	Player& m_playerRef;
public:
	Enemy(Player& player, Camera& camera, Vector2 spawnPos);

	/// <summary>
	/// スクリーンの外かどうか
	/// </summary>
	bool CheckScreenOut() const;
};