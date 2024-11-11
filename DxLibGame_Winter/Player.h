#pragma once
#include "Vector2.h"
#include <memory>

// �����N���X�̃v���g�^�C�v�錾
class Physics;

/// <summary>
/// �v���C���[�̃N���X�ł��B
/// </summary>
class Player
{
private:
	std::shared_ptr<Physics> m_physics;
public:
	/// <summary>
	/// ������
	/// </summary>
	Player();

	/// <summary>
	/// ���͂�����Ĉړ������艽����
	/// </summary>
	/// <returns></returns>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
};

