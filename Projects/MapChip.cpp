#include "Animation.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "game.h"
#include "Image.h"
#include "MapChip.h"
#include "MapConstants.h"
#include "MapImageStore.h"
#include "MapSystem.h"
#include "ObjectsController.h"
#include "Player.h"
#include "SceneController.h"
#include "SceneGame.h"
#include <DxLib.h>

namespace
{
	const std::string kMarineAnimPath = "MarineMapAnimation.png";
	constexpr int kMarineAnimImageSize = 32;
	constexpr float kMarineExRate = MapConstants::kChipSize / kMarineAnimImageSize;
}

void MapChip::ResetMapData()
{
	// �}�b�v�f�[�^�ɖ₢���킹�ă}�b�v�������炤
	m_mapChipData = m_system.GetMapChipData(m_mapPos);
	// �摜
	m_chipImage->SetGraph(m_mapChipData.graphHandle);
	m_backDecorationImage->SetGraph(m_mapChipData.decorationGraphHandle);
	m_backGroundImage->SetGraph(m_mapChipData.backGroundHandle);

	// �������̈ʒu�̃I�u�W�F�N�g���o����Ȃ�o��
	if (m_objCont.lock()->CanSpawnObject(m_mapPos))
	{
		m_objCont.lock()->SpawnObject(m_mapChipData.objKind, m_pos, m_mapPos);
	}

	// �����̓����蔻���ݒ肷��
	// ����̃R���C�_�[���L���łȂ�->�����͗L��
	m_collider->SetIsLineValid(LineDir::Top,    !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x,     m_mapPos.y - 1))); // ��
	m_collider->SetIsLineValid(LineDir::Bottom, !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x,     m_mapPos.y + 1))); // ��
	m_collider->SetIsLineValid(LineDir::Left,   !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x - 1, m_mapPos.y))); // ��
	m_collider->SetIsLineValid(LineDir::Right,  !m_system.GetMapChipCollidable(Vector2Int(m_mapPos.x + 1, m_mapPos.y))); // �E
}

bool MapChip::LoopScreen()
{
	// �����̍��W������͈̔͊O�ɏo�Ă���
	// ���Α��ɏu�Ԉړ�
	// ��ƍ��������D��(�łȂ���1�t���[���̂����ɔ��������т���)

	Vector2 screenPos = m_camera.Capture(m_pos);
	bool isLoop = false;

	if (CheckLoopUp(screenPos))
	{
		SetLoopPosUp();
		isLoop = true;
	}
	else if (CheckLoopDown(screenPos))
	{
		SetLoopPosDown();
		isLoop = true;
	}

	if (CheckLoopLeft(screenPos))
	{
		SetLoopPosLeft();
		isLoop = true;
	}
	else if (CheckLoopRight(screenPos))
	{
		SetLoopPosRight();
		isLoop = true;
	}

	return isLoop;
}

bool MapChip::CheckLoopUp(const Vector2& screenPos) const
{
	return screenPos.y <= -MapConstants::kChipOffset;
}

bool MapChip::CheckLoopDown(const Vector2& screenPos) const
{
	return screenPos.y >= Game::kScreenHeight + MapConstants::kChipOffset;
}

bool MapChip::CheckLoopRight(const Vector2& screenPos) const
{
	return screenPos.x >= Game::kScreenWidth + MapConstants::kChipOffset;
}

bool MapChip::CheckLoopLeft(const Vector2& screenPos) const
{
	return screenPos.x <= -MapConstants::kChipOffset;
}

void MapChip::SetLoopPosUp()
{
	// �ォ�牺��
	m_pos.y += Game::kScreenHeight + MapConstants::kChipOffset * 2;
	m_mapPos.y += MapConstants::kHeightChipNum;
}

void MapChip::SetLoopPosDown()
{
	// ��������
	m_pos.y -= Game::kScreenHeight + MapConstants::kChipOffset * 2;
	m_mapPos.y -= MapConstants::kHeightChipNum;
}

void MapChip::SetLoopPosRight()
{
	// �E�[���獶�[��
	m_pos.x -= Game::kScreenWidth + MapConstants::kChipOffset * 2;
	m_mapPos.x -= MapConstants::kWidthChipNum;
}

void MapChip::SetLoopPosLeft()
{
	// ������E��
	m_pos.x += Game::kScreenWidth + MapConstants::kChipOffset * 2;
	m_mapPos.x += MapConstants::kWidthChipNum;
}

MapChip::MapChip(Camera& camera, const Vector2 initPos, const Vector2Int initMapPos, MapSystem& system) :
	GameObject(initPos),
	m_camera(camera),
	m_mapPos(initMapPos),
	m_system(system)
{
	m_collider            = std::make_shared<BoxCollider>(m_pos, MapConstants::kChipSize, MapConstants::kChipSize);
	m_chipImage           = std::make_shared<Image>      (-1);
	m_backDecorationImage = std::make_shared<Image>      (-1);
	m_backGroundImage     = std::make_shared<Image>      (-1);
	m_marineAnimation     = std::make_shared<Animation>  ();
	m_objCont = std::static_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene())->GetObjectsController();

	m_chipImage->SetExRate(MapConstants::kExRate);
	m_backDecorationImage->SetExRate(MapConstants::kExRate);
	m_backGroundImage->SetExRate(MapConstants::kExRate);
	m_marineAnimation->Init(kMarineAnimPath, 32, 30);
	m_marineAnimation->SetExRate(kMarineExRate);
	m_marineAnimation->SetBlendMode(DX_BLENDMODE_ALPHA, 128);

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
#if _DEBUG
		//printf("MapPos:x=%d,y=%d\n", m_mapPos.x, m_mapPos.y);
#endif
	}

	// movePos��0,0�Ń��Z�b�g
	m_movePos = Vector2();

	m_marineAnimation->Update();
}

void MapChip::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);


	if (m_mapChipData.environment == MapConstants::kEnvironment::kWater)
	{
		m_marineAnimation->Draw(drawPos);
	}
	m_backDecorationImage->Draw(drawPos);
	m_chipImage->Draw(drawPos);

#if _DEBUG
	DrawPixel(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), 0xff0000);
	DrawFormatString(static_cast<int>(drawPos.x) - 20, static_cast<int>(drawPos.y), 0xff0000, "X;%d\nY:%d", m_mapPos.x, m_mapPos.y);

	m_collider->DrawColliderRange_Debug(m_camera.DrawOffset());
#endif
}

void MapChip::BackDraw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_backGroundImage->Draw(drawPos);
}

bool MapChip::CanCollide() const
{
	// ����ς�������
	return m_chipImage->GraphHandle() != -1;
}

MapChipData MapChip::GetMapChipData() const
{
	return m_mapChipData;
}

void MapChip::ChangeGraph_Debug()
{
	m_chipImage->SetGraph(MapImageStore::GetInstance().GetGraph(158));
}
