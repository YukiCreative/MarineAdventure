#include "Camera.h"
#include "ColliderTestScene.h"
#include "game.h"
#include "HPUI.h"
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
#include "Statistics.h"
#include "TileImage.h"
#include "Time.h"
#include <DxLib.h>
#include <cassert>

namespace
{
	const Vector2 kScreenMiddlePos(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	//                                    ��Platinum��X  ���VY
	const Vector2 Stage1PlayerInitPos = { 80 * (3 - 8), 80 * (35 - 5) };
	const Vector2 Stage2PlayerInitPos = { 80 * (3 - 8), 80 * (8 - 5) };
	const Vector2 Stage3PlayerInitPos = { 80 * (6 - 8), 80 * (125 - 5) };
	const Vector2 initHpUIPos   = { kScreenMiddlePos.x - 256, kScreenMiddlePos.y + 300 };
	const std::string kStage1Pass = "Data/MapData/Stage1.fmf";
	const std::string kStage2Pass = "Data/MapData/Stage2.fmf";
	const std::string kStage3Pass = "Data/MapData/Stage3.fmf";
	const std::string kBackGroundPass  = "Marine.jpg";
	const std::string kBackGroundTile  = "WaterBackWallTile.png";
}

Stages SceneGame::s_nowStage = Stages::kStage1;

void SceneGame::MapChangeUpdate()
{
	m_fade.Update();
	// �v���C���[�̃A�j���V�����������s������
	m_player->AnimationUpdate();

	if (m_fade.IsFading()) return;

	m_objectCont->ClearObjects();
	ChangeMap(m_nextMapPath, m_playerTransportPos);
	m_fade.Fade(60, 0);
	// �g�Ɏ��߂�
	m_camera->FitMap();
	m_isMapChanging = false;
}

void SceneGame::HitStopUpdate()
{
	// �Q�[���̍X�V�͍s��Ȃ����A�J�����ƁA�}�b�v�`�b�v�̍X�V�͂�����
	m_camera->Update();
	m_map->Update();
}

SceneGame::SceneGame() :
	m_frameCount(0),
	m_nextMapPath(),
	m_playerTransportPos(),
	m_isMapChanging(false),
	m_stopFrame(0)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_hpUI = std::make_shared<HitPoints>(initHpUIPos);
	m_player = std::make_shared<Player>(*m_camera, Vector2::Zero(), *m_hpUI);
	m_objectCont = std::make_shared<ObjectsController>(*m_camera, *m_player);
	m_map = std::make_shared<MapSystem>();

	// ���̐i�s�x�ɉ����ēǂݍ��ރ}�b�v��ς���
	// switch�ł����ł��傤
	switch (s_nowStage)
	{
	case Stages::kStage1:
		m_map->InitMap(*m_camera, kStage1Pass, *m_objectCont);
		m_player->Teleportation(Stage1PlayerInitPos);
		m_camera->Move(Stage1PlayerInitPos);
		break;
	case Stages::kStage2:
		m_map->InitMap(*m_camera, kStage2Pass, *m_objectCont);
		m_player->Teleportation(Stage2PlayerInitPos);
		m_camera->Move(Stage2PlayerInitPos);
		break;
	case Stages::kStage3:
		m_map->InitMap(*m_camera, kStage3Pass, *m_objectCont);
		m_player->Teleportation(Stage3PlayerInitPos);
		m_camera->Move(Stage3PlayerInitPos);
		break;
	default:
		assert(false && "�悭�킩���X�e�[�W���ǂݍ��܂ꂽ");
		break;
	}

	// ���������Q�ƂŎ��Ȃ��Ⴂ�������
	m_player->Init(m_map, m_objectCont);
	m_camera->SetFollowObject(m_player);
	m_camera->SetMapSize(m_map->GetMapSize());
	m_objectCont->ResetObjectSpawnStatus(*m_map);
	m_camera->FitMap();
}

void SceneGame::GameClear()
{
	SceneChangeWithFadeOut("Clear");
}

void SceneGame::GameOver()
{
	// ���X�e�[�W�̃X�R�A�͖���
	Statistics::GetInstance().ResetNowStageScore();
	// �����Ń|�[�Y���J����(�t�F�[�h�̐F���ς���Ă���)�z������Ȃ��Ƃ����Ȃ��̂��s��
	m_fade.SetColor(0x000000);
	SceneChangeWithFadeOut("Gameover", 120);
}

void SceneGame::ChangeMapWithFadeOut(const Stages stage, const std::string& path, const Vector2& playerTransferPos)
{
	Statistics::GetInstance().SaveScore();
	// �^����ꂽ�����o���Ă���
	s_nowStage = stage;
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
	m_map->ChangeMapData(path, *m_objectCont);
	m_camera->SetMapSize(m_map->GetMapSize());
}

void SceneGame::ChangeMap(const std::string& path, const Vector2& playerTransferPos)
{
	// �ʂ�fmf�t�@�C����ǂݍ��߂΂�������
	m_map->ChangeMapData(path, *m_objectCont);
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
	Statistics::GetInstance().IncreaseTimer();

	// �t���O�Ő\����Ȃ�
	if (m_stopFrame > 0)
	{
		HitStopUpdate();
		--m_stopFrame;
		return;
	}
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
		GameClear();
		//SceneChangeWithFadeOut("Gameover");
		//ChangeMapWithFadeOut("Data/MapData/TestMapGroundStage.fmf", Vector2(-100, 0));
		return;
	}
#endif
}

void SceneGame::Draw() const
{
	m_map->DrawBackGround();
	m_objectCont->DrawBehindMapObject();
	m_map->Draw();
	m_objectCont->DrawFrontMapObject();
	m_player->Draw();
	m_hpUI->Draw();
	m_fade.Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0x999999, "SceneGame ����%d�t���[���o�ߒ�", m_frameCount);
	DrawFormatString(0, 60, 0x999999, "%fFPS", Time::FPS());
	DrawFormatString(0, 75, 0x999999, "deltaTime:%f", Time::DeltaTime());
	DrawFormatString(0, 90, 0x999999, "Camera�̃��[���h���W:x,%f y,%f", m_camera->GetPos().x, m_camera->GetPos().y);

	DrawFormatString(0, 105, 0xffffff, "�R�C���̐�%d", Statistics::GetInstance().GetCoinNum());
#endif
}

void SceneGame::HitStop(const int frame)
{
	m_stopFrame = frame;
}

void SceneGame::ResetStageProgress()
{
	s_nowStage = Stages::kStage1;
}
