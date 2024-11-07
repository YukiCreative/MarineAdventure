#pragma once
#include "Vector2.h"
#include <memory>

// �����N���X�̃v���g�^�C�v�錾
class Rigid;

/// <summary>
/// �v���C���[�̃N���X�ł��B
/// </summary>
class Player
{
private:
	std::shared_ptr<Rigid> m_rigid;
public:
	/// <summary>
	/// ������
	/// </summary>
	Player();

	/// <summary>
	/// ���͂�����Ĉړ������艽����
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
};

