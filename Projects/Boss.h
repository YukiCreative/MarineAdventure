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
	int m_attackInterval;

	using StateFunc_t = void (Boss::*)();
	StateFunc_t m_state;

	void Idle();
	void Charge();
	void Attack();
	void Stun();
	// �v���C���[���_���[�W�𕉂�����
	void Attacked();
	void Damage();
	void Death();

	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_idleAnim;
	std::shared_ptr<Animation> m_attackAnim;
	std::shared_ptr<Animation> m_damageAnim;
	// ���ɐH�炢����A
	// �͖̂��G
	std::shared_ptr<CircleCollider> m_headCol;
	std::shared_ptr<BoxCollider> m_bodyCol;

	void GameClear();

	void HitToPlayer();
	// �v���C���[���_���[�W���󂯂Ȃ��Փ�
	void HitToPlayerSafety();
	bool CheckIsPlayerAttackState();
	void ChangeState(StateFunc_t nextState);
	void SetAttackInterval();
public:
	Boss(ObjectsController& cont, Player& player, Camera& camera, const Vector2& initPos, const Vector2Int& baseMappPos);

	void Update() override;
	void Draw() const override;
};