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
	bool m_isDeleted;
public:
	GameObject() : m_pos(), m_isDeleted(false) {}
	GameObject(Vector2 pos) : m_pos(pos), m_isDeleted(false) {}

	virtual void Update() = 0;
	virtual void Draw() const = 0;

	/// <summary>
	/// ���W��Ԃ�
	/// </summary>
	/// <returns>���W�̎Q��</returns>
	Vector2 GetPos() const { return m_pos; }

	/// <summary>
	/// ����ł邩�ǂ���
	/// </summary>
	bool IsDead() const { return m_isDeleted; }
};