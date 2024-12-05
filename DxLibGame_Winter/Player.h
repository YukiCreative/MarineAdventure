#pragma once
#include "Vector2.h"
#include <memory>
#include "GameObject.h"
#include <string>

// �v���g�^�C�v�錾
class Physics;
class CircleCollider;
class Camera;
class Input;
class MapSystem;

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
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<CircleCollider> m_collider;

	std::weak_ptr<MapSystem> m_map;
	Camera& m_camera;

	using StateFunc_t = void(Player::*)(Input& input, Vector2& axis);
	// ���̃v���C���[�̏��
	StateFunc_t m_state;
	// ���ō��̏�Ԃ�����
	std::string m_graphic;
	// ���݂̏�Ԃ����t���[���������Ă��邩�@�Ƃ��Ɏg���܂�
	int m_stateFrameCount;
	// �̗�
	int m_hp;
	int m_graphHandle;

	void Normal(Input& input, Vector2& axis);
	void Move(Input& input, Vector2& axis);
	void Dash(Input& input, Vector2& axis);
	void Attack(Input& input, Vector2& axis);
	void StrongAttack(Input& input, Vector2& axis);
	void Damage(Input& input, Vector2& axis);
	void Death(Input& input, Vector2& axis);

	void SetStateNormal();

public:
	/// <summary>
	/// ������
	/// </summary>
	Player(Camera& camera, Vector2 spawnPos);

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
	/// ������Physics��velocity��Ԃ�
	/// </summary>
	/// <returns>�����̕����N���X�̑��x</returns>
	Vector2 GetVel() const;

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
};

