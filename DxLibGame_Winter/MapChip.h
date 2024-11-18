#pragma once
#include "Vector2.h"
#include <memory>
#include "GameObject.h"

class BoxCollider;
class Camera;

/// <summary>
/// �}�b�v�`�b�v����̉摜��S������
/// MapSystem��������Œ�z��Ŏ���
/// </summary>
class MapChip : public GameObject
{
private:
	/// <summary>
	/// ���������}�b�v�̂ǂ̃`�b�v��S�����Ă��邩���L��
	/// </summary>
	Vector2 m_mapPos;
	/// <summary>
	/// �������L��
	/// </summary>
	Vector2 m_movePos;
	/// <summary>
	/// �摜�̃n���h��
	/// </summary>
	int m_graphHandle;
	/// <summary>
	/// �����蔻��
	/// </summary>
	std::shared_ptr<BoxCollider> m_collider;
	// �J��������
	Camera& m_camera;

	/// <summary>
	/// ��������ʊO�ɏo�Ă��邩���`�F�b�N���āA
	/// �����Ȃ�Έ�����邩�̂悤�ɍ��W���ړ�������
	/// </summary>
	/// <returns>true:��ʊO�����ʂ��� false:��ʓ��ł���</returns>
	bool LoopScreen();
	bool CheckLoopUpAndLeft();
	bool CheckLoopDownAndRight();
public:
	MapChip(Camera& camera);

	/// <summary>
	/// �X�V����
	/// ��ʊO�ɏo���������Ė߂��Ă���
	/// �V�����摜���擾����
	/// </summary>
	void Update();

	/// <summary>
	/// �����`��
	/// </summary>
	void Draw();

	/// <summary>
	/// MapSystem����w�����󂯂�
	/// </summary>
	/// <param name="">���ݒn����ǂꂾ����������</param>
	void Move(Vector2 moveValue) { m_movePos += moveValue; }

	/// <summary>
	/// ���W�Ԃ�
	/// </summary>
	/// <returns>���W</returns>
	Vector2 GetPos() { return m_pos; }

	/// <summary>
	/// �Ԃ�����
	/// �Ȃ񂩎󂯓n�����ʓ|�ɂȂ��Ă�����
	/// </summary>
	/// <returns>�}�b�v�`�b�v�̃R���C�_�[</returns>
	BoxCollider& GetCollider() { return *m_collider; }

	/// <summary>
/// ���݂̃}�b�v�̃f�[�^���Q�Ƃ��āA
/// �����̎��O���t�f�[�^�����߂�
/// </summary>
	void SetGraph();
};

