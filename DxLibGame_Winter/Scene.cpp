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
	// 遷移条件：フェードが終わる
	// 遷移先：別のシーン
	if (m_fade.IsFading()) return;

	SceneController::GetInstance().ChangeScene(m_fadedNextScene);
}

void Scene::SceneStackUpdate()
{
	m_fade.Update();
	// 遷移条件：フェードが終わる
	// 遷移先：別のシーン
	// でもこっちはシーンを重ねる
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
	// 次のシーンを記憶
	m_fadedNextScene = nextSceneId;
	// フェードに指示を出す
	m_fade.Fade(toralFrame, percent);
	// 自身はフェード待ち状態へ
	m_update = &Scene::SceneChangeUpdate;
}

void Scene::SceneStackWithFadeOut(const std::string& nextSceneId, const int& toralFrame, const float& percent)
{
	m_fadedNextScene = nextSceneId;
	m_fade.Fade(toralFrame, percent);
	// 自身はフェード待ち状態へ(スタック)
	m_update = &Scene::SceneStackUpdate;
}

void Scene::SceneRemoveWithFadeOut(const int& toralFrame, const float& percent)
{
	m_fade.Fade(toralFrame, percent);
	m_update = &Scene::SceneRemoveUpdate;
}
