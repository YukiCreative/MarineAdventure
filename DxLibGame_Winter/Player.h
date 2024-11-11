#pragma once
#include "Vector2.h"
#include <memory>

// �����N���X�̃v���g�^�C�v�錾
class Physics;
class MapSystem;

/// <summary>
/// �v���C���[�̃N���X�ł��B
/// </summary>
class Player
{
private:
	std::shared_ptr<Physics> m_physics;
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
};

