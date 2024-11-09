#include "MapSystem.h"
#include <DxLib.h>
#include <cassert>
#include "game.h"
#include "MapChip.h"
#include "MapImageStore.h"

namespace
{
	// �}�b�v�`�b�v���m�̊Ԋu
	constexpr int kChipSpace = 32;
	// ����ϐ��ɂ��邩��
	constexpr int kWidthChipNum = Game::kScreenWidth / kChipSpace;
	constexpr int kHeightChipNum = Game::kScreenHeight / kChipSpace;
}

MapSystem::MapSystem() :
	m_widthChipNum(kWidthChipNum),
	m_heightChipNum(kHeightChipNum),
	m_mapPos()
{
	// �}�b�v�`�b�v�̃������m��
	for (auto& chip : m_mapChips)
	{
		chip = std::make_shared<MapChip>();
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
		
	}
}
