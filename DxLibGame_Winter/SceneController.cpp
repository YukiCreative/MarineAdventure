#include "SceneController.h"
#include "Scene.h"

// Scene�̊֐������̂܂܎��s
void SceneController::Update()
{
	m_scene.Update();
}

void SceneController::Draw()
{
	m_scene.Draw();
}

void SceneController::ChangeScene(Scene& changeScene)
{
	m_scene = changeScene;
}
