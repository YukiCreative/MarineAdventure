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
	std::array<std::shared_ptr<MapChip>, 17*10> m_mapChips;
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

