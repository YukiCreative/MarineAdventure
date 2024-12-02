#include "MapChip.h"
#include <DxLib.h>
#include "game.h"
#include "MapImageStore.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "MapConstants.h"
#include "ObjectsController.h"

void MapChip::ResetMapData()
{
	// MapImageStore�ɖ₢���킹��
	MapImageStore& mapImageStore = MapImageStore::GetInstance();
	// �Ƃ肠�������͌Œ��
	m_graphHandle = mapImageStore.GetGraph(rand() % 2);
	// �Ƃ肠�����m���œG�����Ƃ��΂����񂿂Ⴄ
	//if (!(rand() % 200))
	//{
	//	m_objectsController.SpawnEnemy(ObjectKinds::kHarmFish, m_pos);
	//}

	// ����A�����Ƀ}�b�v�f�[�^�ɖ₢���킹�ă}�b�v�������炤�`�ɂ���
	// ���炤�̂́A
	// 1.�}�b�v�`�b�v�̃X�v���C�g
	// 2.�����蔻��������Ă��邩�ǂ���
	// 3.�G�̃X�|�[���|�C���g���ǂ����A�ǂ̓G���o���̂��@
	// ������������邽�߂ɁAplatinum�Ŋe���C���[��3�̔z��������Ă��āA
	// ������mapPos�ŎQ�Ƃ���
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

MapChip::MapChip(Camera& camera, ObjectsController& cont, const Vector2 initPos, const Vector2Int initMapPos) :
	GameObject(initPos),
	m_graphHandle(-1),
	m_camera(camera),
	m_objectsController(cont),
	m_mapPos(initMapPos)
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
	}

	// movePos��0,0�Ń��Z�b�g
	m_movePos = Vector2();
	printf("MapPos:x=%d,y=%d\n", m_mapPos.x, m_mapPos.y);
}

void MapChip::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	DrawRotaGraph(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), MapConstants::kExRate, 0, m_graphHandle, true);
#if _DEBUG
	DrawCircle(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), 1, 0xff0000);
#endif
}

void MapChip::SetDebugGraph()
{
	MapImageStore& mapImageStore = MapImageStore::GetInstance();
	m_graphHandle = m_graphHandle = mapImageStore.GetGraph(18);
}