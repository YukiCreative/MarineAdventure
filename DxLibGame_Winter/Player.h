#pragma once
#include "Vector2.h"
#include <memory>
#include "GameObject.h"
#include <string>

// �v���g�^�C�v�錾
class Physics;
class CircleCollider;
class MapSystem;
class Camera;
class Input;

/// <summary>
/// �v���C���[�̃N���X�ł��B
/// </summary>
class Player : public GameObject
{
private:
	std::unique_ptr<Physics> m_physics;
	std::unique_ptr<CircleCollider> m_collider;
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
	Player(Camera& camera);

	/// <summary>
	/// ���͂��Ƃ��Ĉړ������艽������
	/// </summary>
	void Update(MapSystem& map);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// ������Physics��velocity��Ԃ�
	/// ���܂����N���X�Ԃ̃f�[�^�̎󂯓n�����킩��Ȃ�
	/// </summary>
	/// <returns>�����̕����N���X�̑��x</returns>
	Vector2 GetVel() const;

	/// <summary>
	/// �R���C�_�[�Ԃ�����
	/// </summary>
	/// <returns>�R���C�_�[�̃|�C���^</returns>
	CircleCollider& GetCollider();
};