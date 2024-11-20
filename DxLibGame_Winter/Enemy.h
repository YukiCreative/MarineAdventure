#pragma once
#include "GameObject.h"
#include <memory>

class Camera;
class Physics;
class Player;
class EnemyController;

/// <summary>
/// �G�̊��N���X
/// </summary>
class Enemy : public GameObject
{
protected:
	Camera& m_camera;
	int m_hp;
	std::shared_ptr<Physics> m_physics;
	Player& m_playerRef;
	EnemyController& m_controller;
public:
	Enemy(Player& player, Camera& camera, EnemyController& controller, Vector2 spawnPos) :
		GameObject(spawnPos),
		m_camera(camera),
		m_hp(0),
		m_playerRef(player),
		m_controller(controller),
		// ���̕ӂ͔h���N���X���œ���Ă��炨������
		m_physics(nullptr)
	{
	}

	virtual void Update() = 0;
	virtual void Draw() = 0;
};