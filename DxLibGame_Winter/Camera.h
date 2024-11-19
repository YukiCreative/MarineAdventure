#pragma once
#include "Vector2.h"
#include "game.h"
#include <memory>
#include "GameObject.h"

/// <summary>
/// �I�u�W�F�N�g�̃��[���h���W��`��̃X�N���[�����W�ɕϊ�
/// </summary>
class Camera
{
private:
	Vector2 m_pos;
	Vector2 m_drawOffset;
	/// <summary>
	/// Update�ňꊇ�ňړ����邽�߂Ɉꎞ�I�ɋL�����Ă���
	/// </summary>
	Vector2 m_velocity;
	/// <summary>
	/// �Q�Ƃ���Q�[���I�u�W�F�N�g
	/// </summary>
	std::weak_ptr<GameObject> m_refObj;
public:
	/// <summary>
	/// �J�����̍X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �����ɓ����ꂽ���[���h���W���A���݂̃J�����̃��[���h���W�ɂ���ăX�N���[�����W�ɕϊ�
	/// </summary>
	/// <param name="pos">���[���h���W</param>
	/// <returns>�X�N���[�����W</returns>
	Vector2 Capture(const Vector2& objPos) const;
	/// <summary>
	/// �J�����̈ړ�
	/// </summary>
	void Move(Vector2 moveValue) { m_pos += moveValue; }

	Vector2 GetPos() const { return m_pos; };

	/// <summary>
	/// �����ɓ����ꂽ�Q�[���I�u�W�F�N�g�ɒǏ]����
	/// </summary>
	void SetFollowObject(std::weak_ptr<GameObject> obj);
	void ResetFollowObject() { m_refObj.reset(); };
};

