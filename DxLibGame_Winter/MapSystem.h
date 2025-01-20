#pragma once
#include "Vector2.h"
#include <memory>
#include <array>
#include <list>
#include <vector>
#include "MapConstants.h"
#include "MapDataStore.h"
#include "ObjectKind.h"

class kMapChip;
class Player;
class Camera;
class ObjectsController;

using MapArray_t = std::array<std::shared_ptr<kMapChip>, MapConstants::kWidthChipNum* MapConstants::kHeightChipNum>;
using MapList_t  = std::list <std::shared_ptr<kMapChip>>;

struct ObjectAppearanceStatus
{
	bool isExist;
	// �����Ă���̃t���[��
	int frameDisappear;
	// �����Ă��牽�t���[����ɍďo���ł��邩
	int spawnSpan;

	ObjectAppearanceStatus();
	ObjectAppearanceStatus(const ObjectKind& spanKind);

	void IncreaseFrame() { ++frameDisappear; }

	// �f�X�|�[�������Ƃ��Ɏ��s���Ă�
	void Despawn() { frameDisappear = -spawnSpan; }

	bool CanSpawn() const
	{
		// �o�����Ă��Ȃ��āA�����Ă���\���Ɍo�߂���
		return !isExist && frameDisappear > 0;
	}
};

/// <summary>
/// �}�b�v�`�b�v����ׂ�A
/// �}�b�v�`�b�v�𓮂����A
/// �}�b�v�`�b�v��K�؂ɓǂݍ��ށA
/// �}�b�v�`�b�v��K�v�ȕ������\������
/// </summary>
class MapSystem
{
private:
	MapArray_t m_mapChips;
	// ���Ӓl���K�v�Ƃ̂���
	MapList_t m_collidableMapChips;
	// ���}�b�v�̃f�[�^��MapSystem�����悤�ɂ��悤���l����
	std::shared_ptr<MapDataStore> m_mapData;

	// ���̃}�b�v�ɂ���I�u�W�F�N�g���o�����Ă��邩�ǂ������L��
	// ���������ĂȂ��}�X���v�f�ɓ����
	// �����ɒu���Ă������͕�����Ȃ�
	std::vector<ObjectAppearanceStatus> m_isObjectsExist;

	/// <summary>
	/// �}�b�v�`�b�v�̕\���ʒu�����炷
	/// </summary>
	/// <param name="moveValue">���݂̈ʒu����ǂꂾ���ړ������邩</param>
	void MoveMap(Vector2 moveValue);

	void ResetObjectSpawnStatus();
public:
	MapSystem(Camera& camera, ObjectsController& cont, std::string path);

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
	MapArray_t& GetAllMapChips() { return m_mapChips; }

	// �}�b�v�`�b�v�̒�����A�ǂɂȂ��Ă�z�����擾
	MapList_t& GetCollidableMapChips();

	// �^����ꂽ�}�b�v���W���ǂ��ǂ�����Ԃ�
	bool GetMapChipCollidable(const Vector2Int& mapPos) const;

	MapChipData GetMapChipData(const Vector2Int& mapPos) const;
	Vector2Int GetMapSize() const;

	// �ǂݎ��Ȃ���
	void ChangeMapData(const std::string& path);

	// �I�u�W�F�N�g�o���󋵂��擾
	bool CanSpawnObject(const Vector2Int& mapPos) const;

	// �f�X�|�[�������Ƃ��ɌĂ�
	// ����ς���ObjectController�Ɏ�������ׂ��ł�
	void Despawned(const Vector2Int& mapPos);
};

