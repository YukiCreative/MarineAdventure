#pragma once
#include "Vector2.h"
#include <memory>
#include <array>

class MapChip;
class Player;
class Camera;
class EnemyController;

/// <summary>
/// �}�b�v�`�b�v����ׂ�A
/// �}�b�v�`�b�v�𓮂����A
/// �}�b�v�`�b�v��K�؂ɓǂݍ��ށA
/// �}�b�v�`�b�v��K�v�ȕ������\������
/// </summary>
class MapSystem
{
private:
	using MapArray_t = std::array<std::shared_ptr<MapChip>, 17 * 10>;

	MapArray_t m_mapChips;

	/// <summary>
	/// �}�b�v�`�b�v�̕\���ʒu�����炷
	/// </summary>
	/// <param name="moveValue">���݂̈ʒu����ǂꂾ���ړ������邩</param>
	void MoveMap(Vector2 moveValue);
public:
	MapSystem(Camera& camera, EnemyController& cont);

	/// <summary>
	/// ���݂̕`��ꏊ�ɉ����ĕ\������}�b�v�`�b�v�𔻒f
	/// </summary>
	void Update();
	/// <summary>
	/// �}�b�v�`�b�v��`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �}�b�v�`�b�v��������
	/// </summary>
	/// <returns>�}�b�v�`�b�v���ׂ�</returns>
	MapArray_t& GetMapCihps() { return m_mapChips; };
};

