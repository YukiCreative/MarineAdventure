#include "MapSystem.h"
#include <DxLib.h>
#include <cassert>
#include "game.h"
#include "MapChip.h"
#include "MapImageStore.h"
#include "Player.h"
#include "Camera.h"

namespace
{
	// �}�b�v�`�b�v���m�̊Ԋu
	constexpr int kChipSpace = 80;
	// ����ϐ��ɂ��邩��
	constexpr int kWidthChipNum = 16 + 1;
	constexpr int kHeightChipNum = 9 + 1;
}

MapSystem::MapSystem(Camera& camera, EnemyController& cont)
{
	// �}�b�v�`�b�v�̃������m��
	for (auto& chip : m_mapChips)
	{
		chip = std::make_shared<MapChip>(camera, cont);
	}
	// �`�b�v�𓙊Ԋu�Ŕz�u����
	for (int y = 0; y < kHeightChipNum; ++y)
	{
		for (int x = 0; x < kWidthChipNum; ++x)
		{
			m_mapChips[kWidthChipNum * y + x]->
				Move(Vector2(static_cast<float>(kChipSpace * x) - Game::kScreenWidth * 0.5f,
					static_cast<float>(kChipSpace * y) - Game::kScreenHeight * 0.5f));
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
