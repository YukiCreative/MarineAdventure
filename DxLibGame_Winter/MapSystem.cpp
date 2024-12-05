#include "MapSystem.h"
#include <DxLib.h>
#include <cassert>
#include "game.h"
#include "MapChip.h"
#include "MapImageStore.h"
#include "Camera.h"
#include "MapConstants.h"
#include "ObjectsController.h"
#include "MapDataStore.h"

MapSystem::MapSystem(Camera& camera, ObjectsController& cont, std::string pass)
{
	// �}�b�v�f�[�^��������
	m_mapData = std::make_shared<MapDataStore>(pass.c_str());

	// �}�b�v�`�b�v�̃������m��
	// �}�b�v�̏����ʒu��ݒ�
	for (int y = 0; y < MapConstants::kHeightChipNum; ++y)
	{
		for (int x = 0; x < MapConstants::kWidthChipNum; ++x)
		{
			auto& chip = m_mapChips[MapConstants::kWidthChipNum * y + x];
			chip = std::make_shared<MapChip>(camera, cont,
				Vector2(MapConstants::kChipSize * x - Game::kScreenWidth * 0.5f,
						MapConstants::kChipSize * y - Game::kScreenHeight * 0.5f),
				Vector2Int(x,y), *this);
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

void MapSystem::Draw()
{
	for (auto& chip : m_mapChips)
	{
		chip->Draw();
	}
}

void MapSystem::GetMapChipData(const Vector2Int& mapPos, int& handle, ObjectKind& kind)
{
	MapChipData tempData = m_mapData->GetMapData(mapPos);
	handle = tempData.graphHandle;
	kind = tempData.objKind;
}

Vector2Int MapSystem::GetMapSize()
{
	// �E���獶�֎󂯗���
	return m_mapData->GetMapSize();
}

void MapSystem::MoveMap(Vector2 moveValue)
{
	// �S���̍��W�𓙂������炵�Ă�����
	for (auto& chip : m_mapChips)
	{
		chip->Move(moveValue);
	}
}
