#pragma once
#include "GameObject.h"
#include <memory>

class Camera;
class Physics;

/// <summary>
/// 敵の基底クラス
/// </summary>
class Enemy : public GameObject
{
protected:
	Camera& m_camera;
	int m_hp;
	std::shared_ptr<Physics> m_physics;

public:
	Enemy(Camera& camera) :
		m_camera(camera),
		m_hp(0),
		// この辺は派生クラス側で入れてもらおうかな
		m_physics(nullptr)
	{
	}

	virtual void Update() = 0;
	virtual void Draw() = 0;
};