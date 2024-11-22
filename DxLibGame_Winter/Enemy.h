#pragma once
#include "GameObject.h"
#include <memory>

class Camera;
class Physics;
class Player;
class EnemyController;

/// <summary>
/// 敵の基底クラス
/// </summary>
class Enemy : public GameObject
{
protected:
	Camera& m_camera;
	int m_hp;
	bool m_isDead;
	std::shared_ptr<Physics> m_physics;
	Player& m_playerRef;
	EnemyController& m_controller;
public:
	Enemy(Player& player, Camera& camera, EnemyController& controller, Vector2 spawnPos);

	virtual void Update() = 0;
	virtual void Draw() = 0;
	/// <summary>
	/// スクリーンの外かどうか
	/// </summary>
	bool CheckScreenOut() const;
	/// <summary>
	/// 死んでるかどうか
	/// </summary>
	bool IsDead() const { return m_isDead; }
};