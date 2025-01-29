#pragma once
#include "Vector2.h"
#include "ObjectAttribute.h"

// �}�b�v�`�b�v�̗��ɕ`�悳���z�ƁA��ɕ`�悳���z����肽������
enum class DrawPriority
{
	kBehind,
	kFront
};

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
	ObjectAttribute m_att = ObjectAttribute::kOther;
	DrawPriority m_drawP;
public:
	GameObject() : m_pos(), m_isDeleted(false), m_mapPos(), m_drawP(DrawPriority::kFront) {}
	GameObject(const Vector2& pos, const DrawPriority drawP = DrawPriority::kFront) : m_pos(pos), m_isDeleted(false), m_mapPos(), m_drawP(drawP) {}
	GameObject(const Vector2& pos, const Vector2Int& mapPos, const DrawPriority drawP = DrawPriority::kFront) : m_pos(pos), m_isDeleted(false), m_mapPos(mapPos), m_drawP(drawP) {}

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

	void Tere(const Vector2& pos) { m_pos = pos; }
	ObjectAttribute Attribute() const { return m_att; }
	DrawPriority DrawPriority() const { return m_drawP; }
};