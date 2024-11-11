#pragma once
#include "Vector2.h"

/// <summary>
/// �}�b�v�`�b�v����̉摜��S������
/// MapSystem��������Œ�z��Ŏ���
/// </summary>
class MapChip
{
private:
	/// <summary>
	/// ���������}�b�v�̂ǂ̃`�b�v��S�����Ă��邩���L��
	/// </summary>
	Vector2 m_mapPos;

	/// <summary>
	/// ���W
	/// </summary>
	Vector2 m_graphPos;

	/// <summary>
	/// �������L��
	/// </summary>
	Vector2 m_movePos;

	/// <summary>
	/// �摜�̃n���h��
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// ���݂̃}�b�v�̃f�[�^���Q�Ƃ��āA
	/// �����̎��O���t�f�[�^�����߂�
	/// </summary>
	void SetGraph();

	/// <summary>
	/// ��������ʊO�ɏo�Ă��邩���`�F�b�N���āA
	/// �����Ȃ�Έ�����邩�̂悤�ɍ��W���ړ�������
	/// </summary>
	/// <returns>true:��ʊO�����ʂ��� false:��ʓ��ł���</returns>
	bool LoopScreen();
public:
	MapChip();

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
};

