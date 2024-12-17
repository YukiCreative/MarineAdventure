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
	m_system.GetMapChipData(m_mapPos, m_sourceHandle, objKind);
	m_objectsController.SpawnObject(objKind, m_pos);
	// �����̓����蔻���ݒ肷��
	bool isLineValid = m_system.GetMapChipNotCollidable(Vector2Int(m_mapPos.x, m_mapPos.y - 1)); // ��
	m_collider->SetIsLineValid(LineDir::Top, isLineValid);
	isLineValid = m_system.GetMapChipNotCollidable(Vector2Int(m_mapPos.x, m_mapPos.y + 1)); // ��
	m_collider->SetIsLineValid(LineDir::Bottom, isLineValid);
	isLineValid = m_system.GetMapChipNotCollidable(Vector2Int(m_mapPos.x - 1, m_mapPos.y)); // ��
	m_collider->SetIsLineValid(LineDir::Left, isLineValid);
	isLineValid = m_system.GetMapChipNotCollidable(Vector2Int(m_mapPos.x + 1, m_mapPos.y)); // �E
	m_collider->SetIsLineValid(LineDir::Right, isLineValid);
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
	m_sourceHandle(-1),
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
	DrawRotaGraph(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), MapConstants::kExRate, 0, m_sourceHandle, true);
#if _DEBUG
	DrawPixel(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), 0xff0000);
	DrawFormatString(static_cast<int>(drawPos.x) - 20, static_cast<int>(drawPos.y), 0xff0000, "X;%d\nY:%d", m_mapPos.x, m_mapPos.y);
#endif
}

bool MapChip::CanCollide() const
{
	// ����ς�������
	return m_sourceHandle != -1;
}

void MapChip::ChangeGraph_Debug()
{
	m_sourceHandle = MapImageStore::GetInstance().GetGraph(158);
}
