#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include <memory>
#include <string>
#include <list>

// �v���g�^�C�v�錾
class Physics;
class CircleCollider;
class Camera;
class Input;
class MapSystem;
class Animation;

enum class PlayerState
{
	kNormal,
	kMove,
	kDash,
	kAttack,
	kStrongAttack,
	kDamage,
	kDeath
};

/// <summary>
/// �v���C���[�̃N���X�ł��B
/// </summary>
class Player : public GameObject
{
private:
	// �R���|�[�l���g
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<CircleCollider> m_collider;

	std::shared_ptr<Animation> m_nowAnim;
	std::shared_ptr<Animation> m_idleAnim;
	std::shared_ptr<Animation> m_jumpAnim;
	std::shared_ptr<Animation> m_fallAnim;
	std::shared_ptr<Animation> m_damageAnim;
	std::shared_ptr<Animation> m_attackAnim;
	std::shared_ptr<Animation> m_dashAnim;

	std::weak_ptr<MapSystem> m_map;
	Camera& m_camera;

	using StateFunc_t = void(Player::*)(Input& input, Vector2& axis);
	// ���̃v���C���[�̏��
	StateFunc_t m_state;
	// ���ō��̏�Ԃ�����
	std::string m_stateText;
	// ���݂̏�Ԃ����t���[���������Ă��邩�@�Ƃ��Ɏg���܂�
	int m_stateFrameCount;
	// �̗�
	int m_hp;
	// ���t���[���̈ړ��ʂ��L�^�����
	Vector2 m_velocity;
	// ���̃t���[���ɐڐG���������蔻��ŁA�ǂꂾ���߂荞�񂾂����L�^�����
	std::list<Vector2> m_overlaps;
	// ���������������Ă��邩
	bool m_isLeft;

	void GameOver();

	// ��Ԋ֐�
	// ��i�i�グ���ăN���X�ɂ��Ă����������H
	void Normal(Input& input, Vector2& axis);
	void Move(Input& input, Vector2& axis);
	void Dash(Input& input, Vector2& axis);
	void Attack(Input& input, Vector2& axis);
	void StrongAttack(Input& input, Vector2& axis);
	void Damage(Input& input, Vector2& axis);
	void Death(Input& input, Vector2& axis);
	// �G�Ƀ_���[�W��^������̍d��
	void Attacked(Input& input, Vector2& axis);
	// �n��X�e�[�g
	void GNormal(Input& input, Vector2& axis);
	void GMove(Input& input, Vector2& axis);
	void GDash(Input& input, Vector2& axis);
	void Jump(Input& input, Vector2& axis);

	void SetStateNormal();
	bool CheckEnvironmentChanged();
	void CollideToMapChips();
	void ChangeState(StateFunc_t nextState);
	void ChangeAnimation(const std::shared_ptr<Animation>& setAnim);
	void ChangeDirection(const Vector2& axis);
public:
	/// <summary>
	/// ������
	/// </summary>
	Player(Camera& camera, Vector2 spawnPos);
	~Player();

	// �R���X�g���N�^�ł͎擾������Ȃ����̂��擾
	void Init(std::weak_ptr<MapSystem> map) { m_map = map; }

	/// <summary>
	/// ���͂��Ƃ��Ĉړ������艽������
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`��
	/// </summary>
	void Draw() const override;

	/// <summary>
	/// �R���C�_�[�Ԃ�����
	/// </summary>
	/// <returns>�R���C�_�[�̎Q��</returns>
	CircleCollider& GetCollider() const { return *m_collider; }

	/// <summary>
	/// ���݂̏�Ԃ����
	/// </summary>
	/// <param name="stateID"></param>
	/// <returns></returns>
	bool CheckState(PlayerState stateID) const;
	// �_���[�W��^�������Ƃ��ɗ����Ă��炤
	void OnDamage(int damage = 1);
	// physics�̃I�[�o�[���b�v
	void AddForce(const Vector2& force);
	void Stop();
	// �U�����̐U�镑��
	void OnAttack();

	Vector2 GetVel() const { return m_velocity; }
	// �w�肵�����W�ɏu�Ԉړ�
	void Teleportation(Vector2 worldPos) { m_pos = worldPos; }
};