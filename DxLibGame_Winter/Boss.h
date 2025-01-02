#pragma once
#include "Enemy.h"
#include <memory>
#include "Vector2.h"

class Camera;
class Player;
class Animation;
class CircleCollider;
class Player;


// 基底クラスではない
// ボスの名前がきまっていないだけ
class Boss : public Enemy
{
private:
	int m_stateFrameCount;

	using StateFunc_t = void (Boss::*)();
	StateFunc_t m_state;

	void Idle();
	void Damage();
	void Death();

	std::shared_ptr<Animation> m_anim;
	std::shared_ptr<CircleCollider> m_col;
public:
	Boss(Player& player, Camera& camera, Vector2 initPos);

	void Update() override;
	void Draw() const override;
};