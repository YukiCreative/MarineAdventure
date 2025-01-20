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

// ���N���X�ł͂Ȃ�
// �{�X�̖��O�����܂��Ă��Ȃ�����
class Boss : public Enemy
{
private:
	int m_stateFrameCount;

	using StateFunc_t = void (Boss::*)();
	StateFunc_t m_state;

	void Idle();
	// �v���C���[���_���[�W�𕉂�����A���������t�F�[�Y
	void Attacked();
	void Damage();
	void Death();

	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_idleAnim;
	// ���ɐH�炢����A
	// �͖̂��G
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