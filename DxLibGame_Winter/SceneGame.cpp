#include "Camera.h"
#include "ColliderTestScene.h"
#include "game.h"
#include "ImageObject.h"
#include "Input.h"
#include "MapSystem.h"
#include "Music.h"
#include "ObjectKind.h"
#include "ObjectsController.h"
#include "Player.h"
#include "SceneController.h"
#include "SceneGame.h"
#include "SceneGameover.h"
#include "ScenePause.h"
#include "ScreenFade.h"
#include "Time.h"
#include "HPUI.h"
#include <DxLib.h>

namespace
{
	const Vector2 kScreenMiddlePos(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	//                                    ��Platinum��X  ���VY
	const Vector2 initPlayerPos = { 80 * (3 - 8), 80 * (35 - 5) };
	const Vector2 initHpUIPos   = { kScreenMiddlePos.x - 300, kScreenMiddlePos.y + 300 };
	const std::string kInitMapDataPass = "Data/MapData/Stage1.fmf";
	const std::string kBackGroundPass  = "Marine.jpg";
}

void SceneGame::MapChangeUpdate()
{
	m_fade.Update();
	// �v���C���[�̃A�j���V�����������s������
	m_player->AnimationUpdate();

	if (m_fade.IsFading()) return;

	m_objectCont->ClearObjects();
	ChangeMap(m_nextMapPath, m_playerTransportPos);
	m_fade.Fade(60, 0);
	m_isMapChanging = false;
}

SceneGame::SceneGame() :
	m_frameCount(0),
	m_nextMapPath(),
	m_playerTransportPos(),
	m_isMapChanging(false)
{
	m_hpUI       = std::make_shared<HitPoints>        (initHpUIPos);
	m_player     = std::make_shared<Player>           (*m_camera, initPlayerPos, *m_hpUI);
	m_objectCont = std::make_shared<ObjectsController>(*m_camera, *m_player);
	m_map        = std::make_shared<MapSystem>        (*m_camera, *m_objectCont, kInitMapDataPass);
	m_backGround = std::make_shared<ImageObject>      (*m_camera, Vector2::Zero(), kBackGroundPass);

	// ���������Q�ƂŎ��Ȃ��Ⴂ�������
	m_player->Init(m_map);

	m_camera->SetFollowObject(m_player);
	m_camera->SetMapSize(m_map->GetMapSize());
	m_camera->Move(initPlayerPos);
	m_backGround->ExpandGtaph(2.0f);
}

SceneGame::~SceneGame()
{
}

void SceneGame::GameClear()
{
	SceneChangeWithFadeOut("Clear");
}

void SceneGame::GameOver()
{
	// �����Ń|�[�Y���J����(�t�F�[�h�̐F���ς���Ă���)�z������Ȃ��Ƃ����Ȃ��̂��s��
	m_fade.SetColor(0x000000);
	SceneChangeWithFadeOut("Gameover", 120);
}

void SceneGame::ChangeMapWithFadeOut(const std::string& path, const Vector2& playerTransferPos)
{
	// �^����ꂽ�����o���Ă���
	m_nextMapPath = path;
	m_playerTransportPos = playerTransferPos;

	m_fade.Fade(60, 100);
	m_player->Stop();

	// �����̓t�F�[�h�҂���Ԃֈڍs
	// �t���O�Ǘ��͂ق�Ƃ͂������Ȃ���H
	m_isMapChanging = true;
}

void SceneGame::ChangeMap(const std::string& path)
{
	m_map->ChangeMapData(path);
	m_camera->SetMapSize(m_map->GetMapSize());
}

void SceneGame::ChangeMap(const std::string& path, const Vector2& playerTransferPos)
{
	// �ʂ�fmf�t�@�C����ǂݍ��߂΂�������
	m_map->ChangeMapData(path);
	// �V�����}�b�v�̃J�����̐�����c��
	m_camera->SetMapSize(m_map->GetMapSize());
	// �v���C���[�ƃJ�����̈ʒu��ύX
	m_player->Teleportation(playerTransferPos);
	m_camera->Teleport(playerTransferPos);
}

void SceneGame::Entry()
{
	// ��Ƀt�F�[�h
	m_fade.Fade(60, 0);

	Music::GetInstance().Play("Data/Music/���ʂ����̖`��.wav");
	Music::GetInstance().SetVolume(255);
}

void SceneGame::NormalUpdate()
{
	// �}�b�v�J�ڒ��Ȃ炻�����̏���������
	if (m_isMapChanging)
	{
		MapChangeUpdate();
		return;
	}

	Input& input = Input::GetInstance();

	++m_frameCount;
	m_camera->Update();
	m_fade.Update();
	m_hpUI->Update();
	m_map->Update();
	m_player->Update();
	m_objectCont->Update();

	// �J�����̈ړ��ʂ��擾������
	m_backGround->Move(m_camera->GetVel());
	m_backGround->Update();

	if (input.IsTrigger("Pause"))
	{
		// �����Ńt�F�[�h�p�l���̐F�ς����炢���񂶂��
		m_fade.SetColor(0xffffff);
		SceneStackWithFadeOut("Pause", 30);
		return;
	}
#if _DEBUG
	if (input.IsTrigger("ChangeScene_Debug"))
	{
		//SceneChangeWithFadeOut("Clear");
		SceneChangeWithFadeOut("Gameover");
		//ChangeMapWithFadeOut("Data/MapData/TestMapGroundStage.fmf", Vector2(-100, 0));
		return;
	}
#endif
}

void SceneGame::Draw() const
{
	m_backGround->Draw();
	m_map->Draw();
	m_objectCont->Draw();
	m_player->Draw();
	m_hpUI->Draw();
	m_fade.Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0x999999, "SceneGame ����%d�t���[���o�ߒ�", m_frameCount);
	DrawFormatString(0, 60, 0x999999, "%fFPS", Time::FPS());
	DrawFormatString(0, 75, 0x999999, "deltaTime:%f", Time::DeltaTime());
	DrawFormatString(0, 90, 0x999999, "Camera�̃��[���h���W:x,%f y,%f", m_camera->GetPos().x, m_camera->GetPos().y);
#endif
}
