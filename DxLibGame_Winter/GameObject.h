#pragma once
#include "Vector2.h"

/// <summary>
/// ���W������
/// �J�����̒ǔ��Ɏg��
/// </summary>
class GameObject
{
protected:
	// ���W�@���S���W�ŗ���
	Vector2 m_pos;
public:
	/// <summary>
	/// ���W�̎Q�Ƃ�Ԃ�
	/// ���邾���ɂ��Ă��炦��Ə�����܂�
	/// </summary>
	/// <returns>���W�̎Q��</returns>
	Vector2& GetPosRef() { return m_pos; }
};