#pragma once
#include "GameObject.h"
#include <memory>
#include "HitPoint.h"

class Camera;
class Physics;
class Player;
class ObjectsController;

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
	ObjectsController& m_cont;

	Vector2Int m_baseMapPos;
public:
	Enemy(ObjectsController& cont, Player& player, Camera& camera, Vector2 spawnPos);
	~Enemy();

	/// <summary>
	/// スクリーンの外かどうか
	/// </summary>
	bool CheckScreenOut() const;
};