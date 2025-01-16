#pragma once
#include "Enemy.h"
#include <memory>
#include <string>

class CircleCollider;
class Animation;

class HarmFish : public Enemy
{
private:
	int m_stateFrameCount;
	// �ǔ���ԂɈڍs���邩�ǂ�����\�����l
	int m_chasePoint;
	std::shared_ptr<CircleCollider> m_collider;

	// �A�j���[�V�����֘A
	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_idleAnim;
	std::shared_ptr<Animation> m_chaseAnim;
	std::shared_ptr<Animation> m_damageAnim;
	std::shared_ptr<Animation> m_deathAnim;

	// �X�e�[�g
	using StateFunc_t = void (HarmFish::*)();
	StateFunc_t m_state;
	void Idle();
	void Chase();
	void Attacked();
	void Damage();
	void Death();

	// �v���C���[�Ƃ̋����𑪂��āA��ԑJ�ڂ��邽�߂̓_��������
	// ����Ă���΃}�C�i�X�ɁA�߂Â��΃v���X��
	int ScoreChasePoint();
	// �X�R�A����������
	// �X�R�A���N���X�����Ă������Ɏ�������̂��m���ɂ���
	// ���A�߂�ǂ�����
	void ChasePointValidation();

	// �����蔻����܂Ƃ߂�
	void HitToPlayer();
	void HitToMap();

	void ChangeDirection();
	void ChangeState(StateFunc_t nextState);
	void ChangeStateIdle();
public:
	HarmFish(Player& player, Camera& camera, Vector2 spawnPos);
	void Update() override;
	void Draw() const override;
};

