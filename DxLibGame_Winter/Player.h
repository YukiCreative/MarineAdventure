#pragma once
#include "Vector2.h"

/// <summary>
/// �v���C���[�̃N���X�ł��B
/// </summary>
class Player
{
private:
	Vector2 m_pos;
public:
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

