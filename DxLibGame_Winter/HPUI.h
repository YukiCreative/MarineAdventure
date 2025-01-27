#pragma once
#include <array>
#include <memory>
#include "GameObject.h"

class Animation;

// UI
// ���ݑ̗͂������n�[�g���
class HitPointHeart : public GameObject
{
private:
	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_fullAnim;
	std::shared_ptr<Animation> m_emptyAnim;
	std::shared_ptr<Animation> m_damageAnim;

	using State_t = void (HitPointHeart::*)();
	State_t m_state;

	bool m_isFull;

	// ��������Ă����ԂƋ�̏�Ԃ͓�����ԂŊǗ����Ă܂�
	void Normal();
	void Damage();
public:
	HitPointHeart(const Vector2& initPos);

	void Update() override;
	void Draw() const override;

	// �_���[�W���󂯂��Ƃ���
	void OnDamage();
	bool IsFull() const { return m_isFull; }

	void OnRecovery();
};

namespace
{
	constexpr int kMaxHitPoint = 5;
}

// �n�[�g���܂Ƃ߂Ď��s����
// ���₵����A���炵����
class HitPoints : public GameObject
{
private:
	// �ǂ����ő�HP�ς��Ȃ��̂�Array
	std::array<std::shared_ptr<HitPointHeart>, kMaxHitPoint> m_hearts;
public:
	HitPoints(const Vector2& initPos);

	void Update() override;
	void Draw() const override;

	// �v���C���[����Ă�
	void OnDamage(const int damageAmount = 1);
	void OnRecovery(const int recoverAmount = 1);
};