#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "MapImageStore.h"

namespace
{
	// �����_�ł̃}�b�v�`�b�v�̈�ӂ̔����̃s�N�Z��
	// DrawRectGraph�͉摜�̒��S�����_�Ȃ̂ł����Ȃ�
	constexpr int kChipOffset = 16;
}

void MapChip::SetGraph()
{
	// MapImageStore�ɖ₢���킹��
	MapImageStore& mapImageStore = MapImageStore::GetInstance();
	// �Ƃ肠�������͌Œ��
	m_graphHandle = mapImageStore.GetGraph(3);
}

bool MapChip::LoopScreen()
{
	// �����̍��W������͈̔͊O�ɏo�Ă���
	// ���Α��ɏu�Ԉړ�
	
	// �����������
	bool isLoop = false;
	if (m_graphPos.x < -kChipOffset)
	{
		m_graphPos.x = Game::kScreenWidth + kChipOffset;
		isLoop = true;
	}
	if (m_graphPos.x > Game::kScreenWidth + kChipOffset)
	{
		m_graphPos.x = -kChipOffset;
		isLoop = true;
	}
	if (m_graphPos.y < -kChipOffset)
	{
		m_graphPos.y = Game::kScreenHeight + kChipOffset;
		isLoop = true;
	}
	if (m_graphPos.y > Game::kScreenHeight + kChipOffset)
	{
		m_graphPos.y = -kChipOffset;
		isLoop = true;
	}
	return isLoop;
}

MapChip::MapChip() :
	m_graphHandle(-1)
{
	SetGraph();
}

void MapChip::Update()
{
	m_graphPos.x++;
	m_graphPos.y++;

	bool isLoop = LoopScreen();
	// �u�Ԉړ����N��������摜���Ď擾
	if (isLoop)
	{
		SetGraph();
	}
}

void MapChip::Draw()
{
	DrawRotaGraph(m_graphPos.x, m_graphPos.y, 2.0, 0, m_graphHandle, true);
}
