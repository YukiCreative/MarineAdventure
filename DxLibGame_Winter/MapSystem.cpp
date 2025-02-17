#include "Camera.h"
#include "game.h"
#include "MapChip.h"
#include "MapConstants.h"
#include "MapDataStore.h"
#include "MapImageStore.h"
#include "MapSystem.h"
#include "ObjectsController.h"
#include <cassert>
#include <DxLib.h>
#include <unordered_map>

void MapSystem::InitMap(Camera& camera, std::string path, ObjectsController& cont)
{
	// �}�b�v�f�[�^��������
	m_mapData = std::make_shared<MapDataStore>(path.c_str());

	cont.ResetObjectSpawnStatus(*this);

	// �}�b�v�`�b�v�̃������m��
	// �}�b�v�̏����ʒu��ݒ�
	for (int y = 0; y < MapConstants::kHeightChipNum; ++y)
	{
		for (int x = 0; x < MapConstants::kWidthChipNum; ++x)
		{
			auto& chip = m_mapChips[MapConstants::kWidthChipNum * y + x];
			chip = std::make_shared<MapChip>(camera,
				Vector2(MapConstants::kChipSize * x - Game::kScreenWidth * 0.5f,
					MapConstants::kChipSize * y - Game::kScreenHeight * 0.5f),
				Vector2Int(x, y), *this);
		}
	}
}

void MapSystem::Update()
{
	for (auto& chip : m_mapChips)
	{
		chip->Update();
	}
}

void MapSystem::Draw() const
{
	for (auto& chip : m_mapChips)
	{
		chip->Draw();
	}
}

void MapSystem::DrawBackGround() const
{
	for (auto& chip : m_mapChips)
	{
		chip->BackDraw();
	}
}

MapList_t& MapSystem::GetCollidableMapChips()
{
	// �ǂƂ��ėL���ȃ`�b�v�����s�b�N����
	m_collidableMapChips.clear();
	for (const auto& chip : m_mapChips)
	{
		if (chip->CanCollide())
		{
			m_collidableMapChips.push_back(chip);
		}
	}

	// ���݂̉�ʓ��̕ǂ̐�
	//printf("%d\n", static_cast<int>(m_collidableMapChips.size()));

	return m_collidableMapChips;
}

bool MapSystem::GetMapChipCollidable(const Vector2Int& mapPos) const
{
	// �����瑤�Ń}�b�v�̒[�ł�false��Ԃ��悤�ɋC������
	// MapData�����Ă�̂͂��̃N���X����
	Vector2Int mapsize = m_mapData->GetMapSize();
	if (mapPos.x < 0 ||
		mapPos.y < 0 ||
		mapPos.x > mapsize.x ||
		mapPos.y > mapsize.y)
	{
		return true;
	}
	return m_mapData->GetMapData(mapPos).graphHandle != -1;
}

MapChipData MapSystem::GetMapChipData(const Vector2Int& mapPos) const
{
	return  m_mapData->GetMapData(mapPos);
}

Vector2Int MapSystem::GetMapSize() const
{
	// �E���獶�֎󂯗���
	return m_mapData->GetMapSize();
}

void MapSystem::ChangeMapData(const std::string& path, ObjectsController& cont)
{
	m_mapData->LoadMapData(path);

	cont.ResetObjectSpawnStatus(*this);

	// �}�b�v�`�b�v���ēǂݍ���
	// �ʂ̊֐��ɐ؂藣���Ă���������
	for (auto& chip : m_mapChips)
	{
		chip->ResetMapData();
	}
}

ObjectKind MapSystem::GetObjKind(const int& index)
{
	return m_mapData->GetObjKind(index);
}

ObjectKind MapSystem::GetObjKind(const Vector2Int& mapPos)
{
	return m_mapData->GetObjKind(mapPos);
}

void MapSystem::MoveMap(Vector2 moveValue)
{
	// �S���̍��W�𓙂������炵�Ă�����
	for (auto& chip : m_mapChips)
	{
		chip->Move(moveValue);
	}
}