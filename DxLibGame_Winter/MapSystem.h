#pragma once
#include "Vector2.h"
#include <memory>
#include <array>

class MapChip;

/// <summary>
/// �}�b�v�`�b�v����ׂ�A
/// �}�b�v�`�b�v�𓮂����A
/// �}�b�v�`�b�v��K�؂ɓǂݍ��ށA
/// �}�b�v�`�b�v��K�v�ȕ������\������
/// </summary>
class MapSystem
{
private:
	/// <summary>
	/// ���ł���
	/// ������̓}�b�v�̑f�ނ��W�߂��N���X���쐬���܂���
	/// </summary>
	int m_graphHandle;
	/// <summary>
	/// ���̃}�b�v�`�b�v�̐�
	/// ���̃N���X�̃C���X�^���X�����Ɍ��݂̉�ʃT�C�Y�����Č��߂�
	/// </summary>
	int m_widthChipNum;
	/// <summary>
	/// �c�̃}�b�v�`�b�v�̐�
	/// </summary>
	int m_heightChipNum;
	Vector2 m_mapPos;
	std::array<std::shared_ptr<MapChip>, 16*9> m_mapChips;
public:
	MapSystem();

	/// <summary>
	/// ���݂̕`��ꏊ�ɉ����ĕ\������}�b�v�`�b�v�𔻒f
	/// </summary>
	void Update();
	/// <summary>
	/// �}�b�v�`�b�v��`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �}�b�v�`�b�v�̕\���ʒu�����炷
	/// </summary>
	/// <param name="moveValue">���݂̈ʒu����ǂꂾ���ړ������邩</param>
	void MoveMap(Vector2 moveValue);
};

