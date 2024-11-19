#pragma once
#include "Enemy.h"
class HarmFish : public Enemy
{
private:
	using StateFunc_t = void (HarmFish::*)();
	StateFunc_t m_state;
	void Idle();
	void Damage();
	void Death();
public:
	HarmFish(Camera& camera);
	virtual void Update() override;
	virtual void Draw() override;
};

