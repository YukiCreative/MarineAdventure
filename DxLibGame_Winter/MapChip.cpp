#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "MapImageStore.h"
#include "BoxCollider.h"
#include "Camera.h"

namespace
{
	constexpr float kChipSize = 80.0f;
	constexpr int kImageSize = 16;
	constexpr float kExRate = static_cast<float>(kChipSize) / static_cast<float>(kImageSize);
	// �����_�ł̃}�b�v�`�b�v�̈�ӂ̔����̃s�N�Z��
	// DrawRectGraph�͉摜�̒��S�����_�Ȃ̂ł����Ȃ�
	constexpr int kChipOffset = static_cast<int>(kChipSize * 0.5f);
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
	// �X�N���[�����W���v�Z
	Vector2 screenPos = m_camera.Capture(m_pos);
	// ��ʊO����
	bool isLoop = false;
	if (screenPos.x <= -kChipOffset)
	{
		// ���[�v�̎����Ă���Ȃ̂ɂȂ��
		m_pos.x += Game::kScreenWidth + kChipOffset * 2;
		isLoop = true;
	}
	if (screenPos.y <= -kChipOffset)
	{
		m_pos.y += Game::kScreenHeight + kChipOffset * 2;
		isLoop = true;
	}
	return isLoop;
}

bool MapChip::CheckLoopDownAndRight()
{
	// �X�N���[�����W���v�Z
	Vector2 screenPos = m_camera.Capture(m_pos);
	bool isLoop = false;
	if (screenPos.y >= Game::kScreenHeight + kChipOffset)
	{
		m_pos.y -= Game::kScreenHeight + kChipOffset * 2;
		isLoop = true;
	}
	if (screenPos.x >= Game::kScreenWidth + kChipOffset)
	{
		m_pos.x -= Game::kScreenWidth + kChipOffset * 2;
		isLoop = true;
	}
	return isLoop;
}

MapChip::MapChip(Camera& camera) :
	m_graphHandle(-1),
	m_camera(camera)
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
		//printf("���[�v�I�I");
	}

	// movePos��0,0�Ń��Z�b�g
	m_movePos = Vector2();
}

void MapChip::Draw()
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	DrawRotaGraph(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), kExRate, 0, m_graphHandle, true);
#if _DEBUG
	DrawCircle(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), 1, 0xff0000);
#endif
}
