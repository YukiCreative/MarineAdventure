#include "SceneController.h"
#include "Scene.h"
#include <memory>
#include "SceneTitle.h"

SceneController::SceneController() :
	m_scene(std::make_shared<SceneTitle>()),
	m_changedSceneInThisFrame(false)
{
}

SceneController& SceneController::GetInstance()
{
	static SceneController instance;
	return instance;
}

// Scene�̊֐������̂܂܎��s
void SceneController::Update()
{
	m_changedSceneInThisFrame = false;
	m_scene->Update();
}

void SceneController::Draw()
{
	// �V�[�����؂�ւ���Ă�������s���Ȃ�
	if (m_changedSceneInThisFrame) return;
	m_scene->Draw();
}

void SceneController::ChangeScene(std::shared_ptr<Scene> changeScene)
{
	// �X�}�|
	m_scene = changeScene;
	m_changedSceneInThisFrame = true;
}
