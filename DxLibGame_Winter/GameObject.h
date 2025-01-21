#pragma once
#include "Vector2.h"

/// <summary>
/// ���W������
/// �J�����̒ǔ��Ɏg������
/// ���N���X�ł܂Ƃ߂�Update������
/// </summary>
class GameObject
{
protected:
	// ���W�@���S���W�ŗ���
	Vector2 m_pos;
	// �������o���������̃}�b�v���W
	Vector2Int m_mapPos;
	bool m_isDeleted;
public:
	GameObject() : m_pos(), m_isDeleted(false), m_mapPos() {}
	GameObject(const Vector2& pos) : m_pos(pos), m_isDeleted(false), m_mapPos() {}
	GameObject(const Vector2& pos, const Vector2Int& mapPos) : m_pos(pos), m_isDeleted(false), m_mapPos(mapPos) {}

	virtual void Update() = 0;
	virtual void Draw() const = 0;

	/// <summary>
	/// ���W��Ԃ�
	/// </summary>
	/// <returns>���W�̎Q��</returns>
	Vector2 GetPos() const { return m_pos; }
	Vector2Int GetBaseMapPos() const { return m_mapPos; }

	/// <summary>
	/// ���������ǂ���
	/// ���������Controller���폜����
	/// </summary>
	bool IsDeleted() const { return m_isDeleted; }
};