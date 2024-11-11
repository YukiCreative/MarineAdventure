#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "MapImageStore.h"

namespace
{
	constexpr int kChipSize = 80;
	constexpr int kImageSize = 16;
	constexpr float kExRate = static_cast<float>(kChipSize) / static_cast<float>(kImageSize);
	// �����_�ł̃}�b�v�`�b�v�̈�ӂ̔����̃s�N�Z��
	// DrawRectGraph�͉摜�̒��S�����_�Ȃ̂ł����Ȃ�
	constexpr int kChipOffset = kChipSize * 0.5f;
}

void MapChip::SetGraph()
{
	// MapImageStore�ɖ₢���킹��
	MapImageStore& mapImageStore = MapImageStore::GetInstance();
	// �Ƃ肠�������͌Œ��
	m_graphHandle = mapImageStore.GetGraph(70);
}

bool MapChip::LoopScreen()
{
	// �����̍��W������͈̔͊O�ɏo�Ă���
	// ���Α��ɏu�Ԉړ�
	
	// �����������
	bool isLoop = false;

	// x���W�������Ă��Ȃ���΂��A���Ȃ炙�̔�����X�L�b�v����
	if (m_movePos.x != 0.0f)
	{
		if (m_graphPos.x <= -kChipOffset)
		{
			m_graphPos.x = Game::kScreenWidth + kChipOffset;
			isLoop = true;
		}
		if (m_graphPos.x >= Game::kScreenWidth + kChipOffset)
		{
			m_graphPos.x = -kChipOffset;
			isLoop = true;
		}
	}
	if (m_movePos.y != 0.0f)
	{
		if (m_graphPos.y <= -kChipOffset)
		{
			m_graphPos.y = Game::kScreenHeight + kChipOffset;
			isLoop = true;
		}
		if (m_graphPos.y >= Game::kScreenHeight + kChipOffset)
		{
			m_graphPos.y = -kChipOffset;
			isLoop = true;
		}
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
	// �����̏����͈ړ������[�v����
	m_graphPos += m_movePos;

	bool isLoop = LoopScreen();
	// �u�Ԉړ����N��������摜���Ď擾
	if (isLoop)
	{
		SetGraph();
		printfDx("���[�v�I�I");
	}

	// movePos��0,0�Ń��Z�b�g
	m_movePos = Vector2();
}

void MapChip::Draw()
{
	DrawRotaGraph(m_graphPos.x, m_graphPos.y, kExRate, 0, m_graphHandle, true);
}
