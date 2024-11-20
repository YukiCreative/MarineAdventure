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
	GameObject() : m_pos(){}
	GameObject(Vector2 pos) : m_pos(pos){}

	/// <summary>
	/// ���W��Ԃ�
	/// </summary>
	/// <returns>���W�̎Q��</returns>
	Vector2 GetPos() { return m_pos; }
};