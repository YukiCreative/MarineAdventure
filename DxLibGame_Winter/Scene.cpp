#include "Scene.h"
#include "ScreenFade.h"
#include "SceneController.h"

Scene::Scene() :
	m_fade(ScreenFade::Getinstance()),
	m_fadedNextScene(""),
	m_update(&Scene::NormalUpdate)
{
}

void Scene::Update()
{
	(this->*m_update)();
}

void Scene::SceneChangeUpdate()
{
	m_fade.Update();
	// �J�ڏ����F�t�F�[�h���I���
	// �J�ڐ�F�ʂ̃V�[��
	if (m_fade.IsFading()) return;

	SceneController::GetInstance().ChangeScene(m_fadedNextScene);
}

void Scene::SceneStackUpdate()
{
	m_fade.Update();
	// �J�ڏ����F�t�F�[�h���I���
	// �J�ڐ�F�ʂ̃V�[��
	// �ł��������̓V�[�����d�˂�
	if (m_fade.IsFading()) return;

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
