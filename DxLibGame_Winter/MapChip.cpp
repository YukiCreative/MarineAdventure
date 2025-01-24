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
#include "Image.h"
#include "Animation.h"

namespace
{
	const std::string kMarineAnimPath = "MarineMapAnimation.png";
	constexpr int kMarineAnimImageSize = 32;
	constexpr float kMarineExRate = MapConstants::kChipSize / kMarineAnimImageSize;
}

void kMapChip::ResetMapData()
{
	// �}�b�v�f�[�^�ɖ₢���킹�ă}�b�v�������炤
	m_mapChipData = m_system.GetMapChipData(m_mapPos);
	// �摜
	m_chipImage->SetGraph(m_mapChipData.graphHandle);
	m_backImage->SetGraph(m_mapChipData.backGraphHandle);

	// �������̈ʒu�̃I�u�W�F�N�g���o����Ȃ�o��
	if (m_objectsController.CanSpawnObject(m_mapPos))
	{
		m_objectsController.SpawnObject(m_mapChipData.objKind, m_pos, m_mapPos);
	}

	// �����̓����蔻���ݒ肷��
	// ����̃R���C�_�[���L���łȂ�->�����͗L��
	m_collider->SetIsLineValid(LineDir::Top,    !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x,     m_mapPos.y - 1))); // ��
	m_collider->SetIsLineValid(LineDir::Bottom, !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x,     m_mapPos.y + 1))); // ��
	m_collider->SetIsLineValid(LineDir::Left,   !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x - 1, m_mapPos.y))); // ��
	m_collider->SetIsLineValid(LineDir::Right,  !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x + 1, m_mapPos.y))); // �E
}

bool kMapChip::LoopScreen()
{
	// �����̍��W������͈̔͊O�ɏo�Ă���
	// ���Α��ɏu�Ԉړ�
	// ��ƍ��������D��(�łȂ���1�t���[���̂����ɔ��������т���)
	// �Z���]���ɂ���Ď������Ă���
	return CheckLoopUpAndLeft() || CheckLoopDownAndRight(); // Check�Ƃ����O�t���Ă邯�ǂ����胁���o�ϐ��������Ă܂��B���߂�Ȃ����B
}

bool kMapChip::CheckLoopUpAndLeft()
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

bool kMapChip::CheckLoopDownAndRight()
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

kMapChip::kMapChip(Camera& camera, ObjectsController& cont, const Vector2 initPos, const Vector2Int initMapPos, MapSystem& system) :
	GameObject(initPos),
	m_camera(camera),
	m_objectsController(cont),
	m_mapPos(initMapPos),
	m_system(system)
{
	m_collider        = std::make_shared<BoxCollider>(m_pos, MapConstants::kChipSize, MapConstants::kChipSize);
	m_chipImage       = std::make_shared<Image>      (-1);
	m_backImage       = std::make_shared<Image>      (-1);
	m_marineAnimation = std::make_shared<Animation>  ();

	m_chipImage->SetExRate(MapConstants::kExRate);
	m_backImage->SetExRate(MapConstants::kExRate);
	m_marineAnimation->Init(kMarineAnimPath, 32, 30);
	m_marineAnimation->SetExRate(kMarineExRate);
	m_marineAnimation->SetBlendMode(DX_BLENDMODE_ALPHA, 128);

	ResetMapData();
}

void kMapChip::Update()
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

	m_marineAnimation->Update();
}

void kMapChip::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_backImage->Draw(drawPos);

	if (m_mapChipData.environment == MapConstants::Environment::kWater)
	{
		m_marineAnimation->Draw(drawPos);
	}

	m_chipImage->Draw(drawPos);

#if _DEBUG
	DrawPixel(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), 0xff0000);
	DrawFormatString(static_cast<int>(drawPos.x) - 20, static_cast<int>(drawPos.y), 0xff0000, "X;%d\nY:%d", m_mapPos.x, m_mapPos.y);

	m_collider->DrawColliderRange_Debug(m_camera.DrawOffset());
#endif
}

bool kMapChip::CanCollide() const
{
	// ����ς�������
	return m_chipImage->GraphHandle() != -1;
}

MapChipData kMapChip::GetMapChipData() const
{
	return m_mapChipData;
}

void kMapChip::ChangeGraph_Debug()
{
	m_chipImage->SetGraph(MapImageStore::GetInstance().GetGraph(158));
}
