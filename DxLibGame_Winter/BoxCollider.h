#pragma once
#include "Collider.h"
#include <memory>
#include <array>

class CircleCollider;
class LineCollider;

class BoxCollider : public Collider
{
private:
	/// <summary>
	/// ��`�̉��̑傫��
	/// </summary>
	float m_rectWidth;
	/// <summary>
	/// ��`�̏c�̒���
	/// </summary>
	float m_rectHeight;
	// �l�̐����̂����ǂꂪ�L�������L��
	std::array<bool, 4> m_validLineCol;
	// LineCollider�������Ă݂�
	// �~�Ƌ�`�̓����蔻��Ɏg�p����
	// ��`�Ƌ�`�͂��̂܂܎����̕��ƍ����Ŕ��肷��
	using LineArray_t = std::array<std::shared_ptr<LineCollider>, 4>;
	LineArray_t m_lines;

public:
	BoxCollider(Vector2& pos, float w, float h);

	// ���ꂼ��[�̍��W��Ԃ�
	float Right() const { return m_pos.x + m_rectWidth * 0.5f; };
	float Left() const { return m_pos.x - m_rectWidth * 0.5f; };
	float Top() const { return m_pos.y - m_rectHeight * 0.5f; };
	float Bottom() const { return m_pos.y + m_rectHeight * 0.5f; };
	// �Q�Ƃ�Ԃ��֐��ŁA�����o�ϐ���ҏW���Ȃ��ӎv�������ɂ͖߂�l��const�����Ȃ��Ƃ����Ȃ�
	const LineArray_t& GetLineCol() const { return m_lines; };
	bool GetIsLineValid(int index) const { return m_validLineCol[index]; }
protected:
	/// <summary>
	/// �����蔻��̎擾(�Ή~�`)
	/// </summary>
	/// <param name="other">�~�`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle) const override;
	CollisionStatus CheckHitCircle(const CircleCollider& otherCircle, const Vector2& offset) const override;
	/// <summary>
	/// ��`�Ƌ�`�̓����蔻��
	/// </summary>
	/// <param name="other">��`�̓����蔻��</param>
	/// <returns>�ڐG���Ă��邩�ǂ���</returns>
	CollisionStatus CheckHitBox(const BoxCollider& otherRect) const override;
	CollisionStatus CheckHitBox(const BoxCollider& otherRect, const Vector2& offset) const override;

	virtual CollisionStatus CheckHitLine(const LineCollider& otherLine, const Vector2& offset) const override;
};

