#include "TestScene.h"
#include <DxLib.h>
#include "Player.h"
#include "Time.h"
#include "MapSystem.h"
#include "Input.h"
#include "SceneController.h"
#include "ColliderTestScene.h"
#include "Camera.h"
#include "HarmFish.h"
#include "ObjectsController.h"
#include "ObjectKind.h"

TestScene::TestScene() :
	m_frameCount(0)
{
	Vector2 initPlayerPos(400, 450);
	m_camera = std::make_shared<Camera>(initPlayerPos);
	m_player = std::make_shared<Player>(*m_camera, initPlayerPos);
	m_objectCont = std::make_shared<ObjectsController>(*m_player, *m_camera);
	m_map = std::make_shared<MapSystem>(*m_camera, *m_objectCont, "Data/MapData/TestMapData32x16.fmf");

	m_player->Init(m_map);
	m_camera->SetFollowObject(m_player);
	m_camera->SetMapSize(m_map->GetMapSize());
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	Input& input = Input::GetInstance();

	++m_frameCount;
	// �v���C���[�̍X�V�����œ��肵���ړ��ʂ̏���
	// �}�b�v�ɂԂ�����
	// ���@���ƃ}�b�v�̒[�ɗ������Ƀv���C���[������ɓ����������������Â炢
	// �̂ŁA�V�[���ɑ��݂���J�������F�����ĊԐړI�����ΓI�Ɉړ��𔽉f�����邱�Ƃɂ���
	// �J��������Ă��X�N���[���~�߂�̂͂ނ�����
	m_camera->Update();
	m_player->Update();
	m_map->Update();
	m_objectCont->Update();


	if (input.IsTrigger("ChangeScene_Debug"))
	{
		SceneController::GetInstance().ChangeScene(std::make_shared<ColliderTestScene>());
		return;
	}
}

void TestScene::Draw()
{
	m_map->Draw();
	m_player->Draw();
	m_objectCont->Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0x999999, "TestScene ����%d�t���[���o�ߒ�", m_frameCount);
	DrawFormatString(0, 60, 0x999999, "%fFPS", Time::FPS());
	DrawFormatString(0, 75, 0x999999, "deltaTime:%f", Time::DeltaTime());
	DrawFormatString(0, 90, 0x999999, "Camera�̃��[���h���W:x,%f y,%f", m_camera->GetPos().x, m_camera->GetPos().y);
#endif
}
