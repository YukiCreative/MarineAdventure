#pragma once
#include "Vector2.h"
#include <memory>
#include "GameObject.h"

// �����N���X�̃v���g�^�C�v�錾
class Physics;
class CircleCollider;
class MapSystem;
class Camera;

/// <summary>
/// �v���C���[�̃N���X�ł��B
/// </summary>
class Player : public GameObject
{
private:
	std::shared_ptr<Physics> m_physics;
	std::shared_ptr<CircleCollider> m_collider;
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
	void Draw(std::shared_ptr<Camera> camera) const;

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
	std::shared_ptr<CircleCollider> GetCollider() { return m_collider; }
};

