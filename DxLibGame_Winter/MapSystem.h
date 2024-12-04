#pragma once
#include "Vector2.h"
#include <memory>
#include <array>
#include "MapConstants.h"
#include "MapDataStore.h"
#include "ObjectKind.h"

class MapChip;
class Player;
class Camera;
class ObjectsController;

/// <summary>
/// �}�b�v�`�b�v����ׂ�A
/// �}�b�v�`�b�v�𓮂����A
/// �}�b�v�`�b�v��K�؂ɓǂݍ��ށA
/// �}�b�v�`�b�v��K�v�ȕ������\������
/// </summary>
class MapSystem
{
private:
	using MapArray_t = std::array<std::shared_ptr<MapChip>, MapConstants::kWidthChipNum * MapConstants::kHeightChipNum>;
	MapArray_t m_mapChips;
	// ���}�b�v�̃f�[�^��MapSystem�����悤�ɂ��悤���l����
	std::shared_ptr<MapDataStore> m_mapData;

	/// <summary>
	/// �}�b�v�`�b�v�̕\���ʒu�����炷
	/// </summary>
	/// <param name="moveValue">���݂̈ʒu����ǂꂾ���ړ������邩</param>
	void MoveMap(Vector2 moveValue);
public:
	MapSystem(Camera& camera, ObjectsController& cont, std::string pass);

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

	void GetMapChipData(const Vector2Int& mapPos, int& handle, ObjectKind& kind);
	Vector2Int GetMapSize();
};

