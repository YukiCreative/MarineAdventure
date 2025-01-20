#pragma once
#include "Enemy.h"
#include <memory>
#include "Vector2.h"

class Camera;
class Player;
class Animation;
class CircleCollider;
class BoxCollider;
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
	// プレイヤーがダメージを負った後、情けをかけるフェーズ
	void Attacked();
	void Damage();
	void Death();

	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_idleAnim;
	// 頭に食らい判定、
	// 体は無敵
	std::shared_ptr<CircleCollider> m_headCol;
	std::shared_ptr<BoxCollider> m_bodyCol;

	void GameClear();

	bool CheckIsPlayerAttackState();
	void ChangeState(StateFunc_t nextState);
public:
	Boss(ObjectsController& cont, Player& player, Camera& camera, Vector2 initPos);

	void Update() override;
	void Draw() const override;
};