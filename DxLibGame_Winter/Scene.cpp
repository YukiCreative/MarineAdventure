#include "Scene.h"
#include "ScreenFade.h"
#include "SceneController.h"
#include "Camera.h"

Scene::Scene() :
	m_fade(ScreenFade::Getinstance()),
	m_fadedNextScene(""),
	m_update(&Scene::NormalUpdate),
	m_shakeCount(0)
{
	m_camera = std::make_shared<Camera>();
}

void Scene::Update()
{
	// ��ʂ�h�炷
	if (m_shakeCount > 0)
	{
		m_camera->Move(Vector2(GetRand(5), GetRand(5)));
	}

	(this->*m_update)();
	--m_shakeCount;
}

void Scene::HitStopUpdate()
{
	// ��ʂ�h�炷
	if (m_shakeCount > 0)
	{
		m_camera->Move(Vector2(GetRand(5), GetRand(5)));
	}
	m_camera->Update();
	--m_shakeCount;
}

void Scene::Leave()
{
	// ���N���X�ł͉������Ȃ�
}

void Scene::SceneChangeUpdate()
{
	m_fade.Update();
	// �J�ڏ����F�t�F�[�h���I���
	// �J�ڐ�F�ʂ̃V�[��
	if (m_fade.IsFading()) return;

	SceneController::GetInstance().ChangeScene(m_fadedNextScene);
}

void Scene::SceneResumeUpdate()
{
	m_fade.Update();
	// �J�ڏ����F�t�F�[�h���I���
	if (m_fade.IsFading()) return;

	SceneController::GetInstance().ResumeScene(m_fadedNextScene);
}

void Scene::SceneStackUpdate()
{
	m_fade.Update();
	// �J�ڏ����F�t�F�[�h���I���
	// �J�ڐ�F�ʂ̃V�[��
	// �ł��������̓V�[�����d�˂�
	if (m_fade.IsFading()) return;

	// �A�v�f�����ɖ߂�
	m_update = &Scene::NormalUpdate;

	SceneController::GetInstance().StackScene(m_fadedNextScene);
}

void Scene::SceneRemoveUpdate()
{
	m_fade.Update();
	if (m_fade.IsFading()) return;

	SceneController::GetInstance().RemoveSceme();
}

void Scene::SceneChangeWithFadeOut(const std::string& nextSceneId, const int& toralFrame, const float& percent)
{
	// ���̃V�[�����L��
	m_fadedNextScene = nextSceneId;
	// �t�F�[�h�Ɏw�����o��
	m_fade.Fade(toralFrame, percent);
	// ���g�̓t�F�[�h�҂���Ԃ�
	m_update = &Scene::SceneChangeUpdate;
}

void Scene::SceneResumeWithFadeOut(const std::string& nextSceneId, const int& toralFrame, const float& percent)
{
	m_fadedNextScene = nextSceneId;
	m_fade.Fade(toralFrame, percent);
	m_update = &Scene::SceneResumeUpdate;
}

void Scene::SceneStackWithFadeOut(const std::string& nextSceneId, const int& toralFrame, const float& percent)
{
	m_fadedNextScene = nextSceneId;
	m_fade.Fade(toralFrame, percent);
	// ���g�̓t�F�[�h�҂���Ԃ�(�X�^�b�N)
	m_update = &Scene::SceneStackUpdate;
}

void Scene::SceneRemoveWithFadeOut(const int& toralFrame, const float& percent)
{
	m_fade.Fade(toralFrame, percent);
	m_update = &Scene::SceneRemoveUpdate;
}
