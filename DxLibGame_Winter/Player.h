#pragma once
#include "Vector2.h"
#include <memory>

// �����N���X�̃v���g�^�C�v�錾
class Physics;
class CircleCollider;
class MapSystem;

/// <summary>
/// �v���C���[�̃N���X�ł��B
/// </summary>
class Player
{
private:
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<CircleCollider> m_collider;
	// �����Ђ傤
	Vector2 m_pos;
public:
	/// <summary>
	/// ������
	/// </summary>
	Player();

	/// <summary>
	/// ���͂��Ƃ��Ĉړ������艽������
	/// </summary>
	void Update(const std::shared_ptr<MapSystem> map);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ������Physics��velocity��Ԃ�
	/// ���܂����N���X�Ԃ̃f�[�^�̎󂯓n�����킩��Ȃ�
	/// </summary>
	/// <returns></returns>
	Vector2 GetVel();

	/// <summary>
	/// �R���C�_�[�Ԃ�����
	/// </summary>
	/// <returns>�R���C�_�[�̃|�C���^</returns>
	std::shared_ptr<CircleCollider> Collider() { return m_collider; }
};

