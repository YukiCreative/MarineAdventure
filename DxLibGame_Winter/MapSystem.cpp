#include "MapSystem.h"
#include <DxLib.h>
#include <cassert>
#include "game.h"
#include "MapChip.h"
#include "MapImageStore.h"
#include "Player.h"
#include "Camera.h"
#include "MapConstants.h"
#include "ObjectsController.h"

MapSystem::MapSystem(Camera& camera, ObjectsController& cont)
{
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
				Vector2Int(x -  MapConstants::kWidthChipNum,
						   y -  MapConstants::kHeightChipNum));
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

void MapSystem::MoveMap(Vector2 moveValue)
{
	// �S���̍��W�𓙂������炵�Ă�����
	for (auto& chip : m_mapChips)
	{
		chip->Move(moveValue);
	}
}
