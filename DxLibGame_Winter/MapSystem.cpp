#include "MapSystem.h"
#include <DxLib.h>
#include <cassert>
#include "game.h"
#include "MapChip.h"
#include "MapImageStore.h"
#include "Player.h"

namespace
{
	// �}�b�v�`�b�v���m�̊Ԋu
	constexpr int kChipSpace = 80;
	// ����ϐ��ɂ��邩��
	constexpr int kWidthChipNum = 16 + 1;
	constexpr int kHeightChipNum = 9 + 1;
}

MapSystem::MapSystem()
{
	// �}�b�v�`�b�v�̃������m��
	for (auto& chip : m_mapChips)
	{
		chip = std::make_shared<MapChip>();
	}
	// �`�b�v�𓙊Ԋu�Ŕz�u����
	for (int y = 0; y < kHeightChipNum; ++y)
	{
		for (int x = 0; x < kWidthChipNum; ++x)
		{
			m_mapChips[kWidthChipNum * y + x]->
				Move(Vector2(kChipSpace * x - kChipSpace * 0.5f, kChipSpace * y - kChipSpace * 0.5f));
		}
	}
}

void MapSystem::Update(std::shared_ptr<Player> player)
{
	// ���ΓI�Ƀv���C���[�������Ă���悤�Ɍ�����
	MoveMap(player->GetVel() * -1);

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
