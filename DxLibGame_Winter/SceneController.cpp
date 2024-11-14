#include "SceneController.h"
#include "Scene.h"
#include <memory>
#include "TestScene.h"
#include "ColliderTestScene.h"

SceneController::SceneController() :
	m_scene(std::make_shared<TestScene>())
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
	m_scene->Update();
}

void SceneController::Draw()
{
	m_scene->Draw();
}

void SceneController::ChangeScene(std::shared_ptr<Scene> changeScene)
{
	// �X�}�|
	m_scene = changeScene;
}
