#include "SceneController.h"
#include "Scene.h"
#include <memory>
#include "SceneTitle.h"
#include <cassert>

SceneController::SceneController() :
	m_changedSceneInThisFrame(false)
{
	StackScene(std::make_shared<SceneTitle>());
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
	// ��ԏ�̃V�[���������s
	m_scenes.back()->Update();
}

void SceneController::Draw()
{
	// �V�[�����؂�ւ���Ă�������s���Ȃ�
	if (m_changedSceneInThisFrame) return;
	for (const auto& scene : m_scenes)
	{
		// �`��͑S���ɑ΂��čs��
		scene->Draw();
	}
}

void SceneController::ChangeScene(std::shared_ptr<Scene> changeScene)
{
	// �X�}�|
	m_scenes.back() = changeScene;
	m_changedSceneInThisFrame = true;
}

void SceneController::StackScene(std::shared_ptr<Scene> addScene)
{
	m_scenes.push_back(addScene);
}

void SceneController::RemoveSceme()
{
	assert(m_scenes.size() > 1 && "�V�[���������Ȃ��ł�����");
	m_scenes.pop_back();
}
