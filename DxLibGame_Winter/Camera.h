#pragma once
#include "Vector2.h"
#include "game.h"
#include <memory>
#include "GameObject.h"

class MapSystem;

/// <summary>
/// �I�u�W�F�N�g�̃��[���h���W��`��̃X�N���[�����W�ɕϊ�
/// </summary>
class Camera
{
private:
	Vector2 m_pos;
	// �}�b�v�̃`�b�v����m���Ă�������
	Vector2Int m_mapSize;
	Vector2 m_drawOffset;
	// ����̃t���[���̈ړ��ʂ��L�����Ă���
	Vector2 m_velocity;
	// Move�̈ړ��ʋL���p
	Vector2 m_moveAmount;
	/// <summary>
	/// �Q�Ƃ���Q�[���I�u�W�F�N�g
	/// </summary>
	std::weak_ptr<GameObject> m_refObj;
public:
	Camera() = default;
	// �J�����̏����ʒu�����������悤�ɂ���
	Camera(Vector2 initPos) : m_pos(initPos) {}

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
	void Move(const Vector2& moveValue) { m_moveAmount += moveValue; }
	void Teleport(const Vector2& pos) { m_pos = pos; }

	void SetMapSize(Vector2Int mapSize) { m_mapSize = mapSize; };

	Vector2 GetPos() const { return m_pos; };
	// ��������W��������΃X�N���[�����W�ɂȂ�܂�
	// �ł�������Capture���g���Ăق���
	Vector2 DrawOffset() const { return m_drawOffset; }

	/// <summary>
	/// �����ɓ����ꂽ�Q�[���I�u�W�F�N�g�ɒǏ]����
	/// </summary>
	void SetFollowObject(std::weak_ptr<GameObject> obj) { m_refObj = obj; }
	void ResetFollowObject() { m_refObj.reset(); };
	Vector2 GetVel() { return m_velocity; }
};

