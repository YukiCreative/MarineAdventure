#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "MapImageStore.h"
#include "BoxCollider.h"

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
	m_graphHandle = mapImageStore.GetGraph(rand() % 2);
}

bool MapChip::LoopScreen()
{
	// �����̍��W������͈̔͊O�ɏo�Ă���
	// ���Α��ɏu�Ԉړ�
	// ��ƍ��������D��(�łȂ���1�t���[���̂����ɔ��������т���)
	// �Z���]���ɂ���Ď������Ă���
	return CheckLoopUpAndLeft() || CheckLoopDownAndRight();
}

bool MapChip::CheckLoopUpAndLeft()
{
	// x���W�������Ă��Ȃ���΂��A���Ȃ炙�̔�����X�L�b�v����
	bool isLoop = false;
	if (m_pos.x <= -kChipOffset && m_movePos.x != 0.0f)
	{
		// ���[�v����ۂ̔����Ȃ���𒼂����炱��Ȍv�Z���Ɂc
		m_pos.x = m_pos.x + Game::kScreenWidth + kChipOffset * 2.0f;
		isLoop = true;
	}
	if (m_pos.y <= -kChipOffset && m_movePos.y != 0.0f)
	{
		m_pos.y = m_pos.y + Game::kScreenHeight + kChipOffset * 2.0f;
		isLoop = true;
	}
	return isLoop;
}

bool MapChip::CheckLoopDownAndRight()
{
	// x���W�������Ă��Ȃ���΂��A���Ȃ炙�̔�����X�L�b�v����̂͂����������
	bool isLoop = false;
	if (m_pos.y >= Game::kScreenHeight + kChipOffset && m_movePos.y != 0.0f)
	{
		m_pos.y =  m_pos.y - (Game::kScreenHeight + kChipOffset * 2.0f);
		isLoop = true;
	}
	if (m_pos.x >= Game::kScreenWidth + kChipOffset && m_movePos.x != 0.0f)
	{
		m_pos.x = m_pos.x - (Game::kScreenWidth + kChipOffset * 2.0f);
		isLoop = true;
	}
	return isLoop;
}

MapChip::MapChip() :
	m_graphHandle(-1)
{
	m_collider = std::make_shared<BoxCollider>(m_pos, kChipSize, kChipSize);
	SetGraph();
}

void MapChip::Update()
{
	// �����̏����͈ړ������[�v����
	m_pos += m_movePos;

	// �u�Ԉړ��������āA�N��������摜���Ď擾
	if (LoopScreen())
	{
		SetGraph();
	}

	// movePos��0,0�Ń��Z�b�g
	m_movePos = Vector2();
}

void MapChip::Draw()
{
	DrawRotaGraph(m_pos.x, m_pos.y, kExRate, 0, m_graphHandle, true);
}
