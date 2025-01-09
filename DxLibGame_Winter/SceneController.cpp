#include "SceneController.h"
#include "Scene.h"
#include <memory>
#include "SceneTitle.h"
#include "TestScene.h"
#include "SceneGameover.h"
#include "ColliderTestScene.h"
#include "ScenePause.h"
#include "SceneGameClear.h"
#include <cassert>

SceneController::SceneController()
{
	m_factoryMap["Title"]    = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<SceneTitle>       ());};
	m_factoryMap["Game"]     = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<TestScene>        ());};
	m_factoryMap["Gameover"] = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<SceneGameover>    ());};
	m_factoryMap["ColTest"]  = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<ColliderTestScene>());};
	m_factoryMap["Pause"]    = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<ScenePause>       ());};
	m_factoryMap["Clear"]    = [](){return static_cast<std::shared_ptr<Scene>>(std::make_shared<SceneGameClear>   ());};

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
	// 一番上のシーンだけ実行
	m_scenes.back()->Update();
}

void SceneController::Draw()
{
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
	m_scenes.back()->Entry();

#if _DEBUG
	printf("現在のシーン数：%d\n", static_cast<int>(m_scenes.size()));
#endif
}

void SceneController::ResumeScene(std::string sceneId)
{
	// シーンを一回リセット
	m_scenes.clear();
	StackScene(sceneId);

#if _DEBUG
	printf("現在のシーン数：%d\n", static_cast<int>(m_scenes.size()));
#endif
}

void SceneController::StackScene(std::string addSceneId)
{
	m_scenes.push_back(m_factoryMap.at(addSceneId)());
	m_scenes.back()->Entry();

#if _DEBUG
	printf("現在のシーン数：%d\n", static_cast<int>(m_scenes.size()));
#endif
}

void SceneController::RemoveSceme()
{
	assert(m_scenes.size() > 1 && "シーンが無くなるんですけど");
	m_scenes.pop_back();
	// 戻った時にやりたいことをやる関数を走らせる
	m_scenes.back()->Entry();

#if _DEBUG
	printf("現在のシーン数：%d\n", static_cast<int>(m_scenes.size()));
#endif
}
