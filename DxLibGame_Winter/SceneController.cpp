#include "SceneController.h"
#include "Scene.h"
#include <memory>
#include "SceneTitle.h"
#include "TestScene.h"
#include "SceneGameover.h"
#include "ColliderTestScene.h"
#include "PauseScene.h"
#include <cassert>

SceneController::SceneController() :
	m_changedSceneInThisFrame(false)
{
	m_factoryMap["Title"] = []() {return static_cast<std::shared_ptr<Scene>>(std::make_shared<SceneTitle>()); };
	m_factoryMap["Game"] = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<TestScene>());};
	m_factoryMap["Gameover"] = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<SceneGameover>());};
	m_factoryMap["ColTest"] = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<ColliderTestScene>());};
	m_factoryMap["Pause"] = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<PauseScene>());};

	StackScene("Title");
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

void SceneController::ChangeScene(std::string sceneId)
{
	// 関数を実行
	m_scenes.back() = m_factoryMap.at(sceneId)();
	m_changedSceneInThisFrame = true;
	m_scenes.back()->Entry();
}

void SceneController::StackScene(std::string addSceneId)
{
	m_scenes.push_back(m_factoryMap.at(addSceneId)());
	m_scenes.back()->Entry();
}

void SceneController::RemoveSceme()
{
	assert(m_scenes.size() > 1 && "シーンが無くなるんですけど");
	m_scenes.pop_back();
	// 戻った時にやりたいことをやる関数を走らせる
	m_scenes.back()->Entry();
}
