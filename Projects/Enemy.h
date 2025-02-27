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
public:
	Enemy(ObjectsController& cont, Player& player, Camera& camera, const Vector2& spawnPos, const Vector2Int& baseMapPos);

	/// <summary>
	/// スクリーンの外かどうか
	/// </summary>
	bool CheckScreenOut() const;

	// ObjectControllerが敵を見て、接触していたら離すための関数
	void AddForce(const Vector2& force);
};