#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "MapConstants.h"
#include "ObjectsController.h"
#include "MapSystem.h"
#include "Player.h"
#include "MapImageStore.h"

void MapChip::ResetMapData()
{
	// �}�b�v�f�[�^�ɖ₢���킹�ă}�b�v�������炤
	ObjectKind objKind;
	m_system.GetMapChipData(m_mapPos, m_graphHandle, objKind);
	m_objectsController.SpawnObject(objKind, m_pos);
}

bool MapChip::LoopScreen()
{
	// �����̍��W������͈̔͊O�ɏo�Ă���
	// ���Α��ɏu�Ԉړ�
	// ��ƍ��������D��(�łȂ���1�t���[���̂����ɔ��������т���)
	// �Z���]���ɂ���Ď������Ă���
	return CheckLoopUpAndLeft() || CheckLoopDownAndRight(); // Check�Ƃ����O�t���Ă邯�ǂ����胁���o�ϐ��������Ă܂��B���߂�Ȃ����B
}

bool MapChip::CheckLoopUpAndLeft()
{
	// �X�N���[�����W���v�Z
	Vector2 screenPos = m_camera.Capture(m_pos);
	// ��ʊO����
	bool isLoop = false;
	if (screenPos.x <= -MapConstants::kChipOffset) // ������E��
	{
		// ���[�v�̎����Ă���Ȃ̂ɂȂ��
		m_pos.x += Game::kScreenWidth + MapConstants::kChipOffset * 2;
		m_mapPos.x += MapConstants::kWidthChipNum;
		isLoop = true;
	}
	if (screenPos.y <= -MapConstants::kChipOffset) // �ォ�牺��
	{
		m_pos.y += Game::kScreenHeight + MapConstants::kChipOffset * 2;
		m_mapPos.y += MapConstants::kHeightChipNum;
		isLoop = true;
	}
	return isLoop;
}

bool MapChip::CheckLoopDownAndRight()
{
	// �X�N���[�����W���v�Z
	Vector2 screenPos = m_camera.Capture(m_pos);
	bool isLoop = false;
	if (screenPos.y >= Game::kScreenHeight + MapConstants::kChipOffset) // ��������
	{
		m_pos.y -= Game::kScreenHeight + MapConstants::kChipOffset * 2;
		m_mapPos.y -= MapConstants::kHeightChipNum;
		isLoop = true;
	}
	if (screenPos.x >= Game::kScreenWidth + MapConstants::kChipOffset) // �E�[���獶�[��
	{
		m_pos.x -= Game::kScreenWidth + MapConstants::kChipOffset * 2;
		m_mapPos.x -= MapConstants::kWidthChipNum;
		isLoop = true;
	}
	return isLoop;
}

MapChip::MapChip(Camera& camera, ObjectsController& cont, const Vector2 initPos, const Vector2Int initMapPos, MapSystem& system) :
	GameObject(initPos),
	m_graphHandle(-1),
	m_camera(camera),
	m_objectsController(cont),
	m_mapPos(initMapPos),
	m_system(system)
{
	m_collider = std::make_shared<BoxCollider>(m_pos, MapConstants::kChipSize, MapConstants::kChipSize);
	ResetMapData();
}

void MapChip::Update()
{
	// �����̏����͈ړ������[�v����
	m_pos += m_movePos;

	// �u�Ԉړ��������āA�N��������摜���Ď擾
	if (LoopScreen())
	{
		ResetMapData();
		//printf("���[�v�I�I");
		printf("MapPos:x=%d,y=%d\n", m_mapPos.x, m_mapPos.y);
	}

	// movePos��0,0�Ń��Z�b�g
	m_movePos = Vector2();
}

void MapChip::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	DrawRotaGraph(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), MapConstants::kExRate, 0, m_graphHandle, true);
#if _DEBUG
	DrawCircle(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), 1, 0xff0000);
#endif
}

bool MapChip::CanCollide() const
{
	return m_graphHandle != -1;
}

void MapChip::ChangeGraph_Debug()
{
	m_graphHandle = MapImageStore::GetInstance().GetGraph(158);
}
