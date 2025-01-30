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
	// 画面を揺らす
	if (m_shakeCount > 0)
	{
		m_camera->Move(Vector2(GetRand(5), GetRand(5)));
	}

	(this->*m_update)();
	--m_shakeCount;
}

void Scene::HitStopUpdate()
{
	// 画面を揺らす
	if (m_shakeCount > 0)
	{
		m_camera->Move(Vector2(GetRand(5), GetRand(5)));
	}
	m_camera->Update();
	--m_shakeCount;
}

void Scene::Leave()
{
	// 基底クラスでは何もしない
}

void Scene::SceneChangeUpdate()
{
	m_fade.Update();
	// 遷移条件：フェードが終わる
	// 遷移先：別のシーン
	if (m_fade.IsFading()) return;

	SceneController::GetInstance().ChangeScene(m_fadedNextScene);
}

void Scene::SceneResumeUpdate()
{
	m_fade.Update();
	// 遷移条件：フェードが終わる
	if (m_fade.IsFading()) return;

	SceneController::GetInstance().ResumeScene(m_fadedNextScene);
}

void Scene::SceneStackUpdate()
{
	m_fade.Update();
	// 遷移条件：フェードが終わる
	// 遷移先：別のシーン
	// でもこっちはシーンを重ねる
	if (m_fade.IsFading()) return;

	// アプデを元に戻す
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
	// 次のシーンを記憶
	m_fadedNextScene = nextSceneId;
	// フェードに指示を出す
	m_fade.Fade(toralFrame, percent);
	// 自身はフェード待ち状態へ
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
	// 自身はフェード待ち状態へ(スタック)
	m_update = &Scene::SceneStackUpdate;
}

void Scene::SceneRemoveWithFadeOut(const int& toralFrame, const float& percent)
{
	m_fade.Fade(toralFrame, percent);
	m_update = &Scene::SceneRemoveUpdate;
}
