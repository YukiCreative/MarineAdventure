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

// Sceneの関数をそのまま実行
void SceneController::Update()
{
	m_changedSceneInThisFrame = false;
	// 一番上のシーンだけ実行
	m_scenes.back()->Update();
}

void SceneController::Draw()
{
	// シーンが切り替わっていたら実行しない
	if (m_changedSceneInThisFrame) return;
	for (const auto& scene : m_scenes)
	{
		// 描画は全部に対して行う
		scene->Draw();
	}
}

void SceneController::ChangeScene(std::shared_ptr<Scene> changeScene)
{
	// スマポ
	m_scenes.back() = changeScene;
	m_changedSceneInThisFrame = true;
}

void SceneController::StackScene(std::shared_ptr<Scene> addScene)
{
	m_scenes.push_back(addScene);
}

void SceneController::RemoveSceme()
{
	assert(m_scenes.size() > 1 && "シーンが無くなるんですけど");
	m_scenes.pop_back();
}
