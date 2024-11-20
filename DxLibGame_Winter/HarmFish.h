#pragma once
#include "Enemy.h"
#include <memory>
#include <string>

class CircleCollider;
class EnemyController;

class HarmFish : public Enemy
{
private:
	int m_stateFrameCount;
	using StateFunc_t = void (HarmFish::*)();
	StateFunc_t m_state;
	void Idle();
	void Damage();
	void Death();

	// ‰¼
	std::string m_graphic;
	std::shared_ptr<CircleCollider> m_collider;
	bool m_isDead;
public:
	HarmFish(Player& player, Camera& camera, EnemyController& controller, Vector2 spawnPos);
	virtual void Update() override;
	virtual void Draw() override;
};

