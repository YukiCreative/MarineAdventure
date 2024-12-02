#pragma once
#include "Enemy.h"
#include <memory>
#include <string>

class CircleCollider;

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
public:
	HarmFish(Player& player, Camera& camera, Vector2 spawnPos);
	virtual void Update() override;
	virtual void Draw() const override;
};

