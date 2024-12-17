#pragma once
#include <memory>

// プロトタイプ宣言
class Scene;

/// <summary>
/// シーンを付け替えて実行するクラス
/// シングルトンクラス
/// </summary>
class SceneController
{
private:
	SceneController();
	SceneController(const SceneController&) = delete;
	void operator=(const SceneController&) = delete;

	std::shared_ptr<Scene> m_scene;
	bool m_changedSceneInThisFrame;
public:
	static SceneController& GetInstance();

	void Update();
	void Draw();

	void ChangeScene(std::shared_ptr<Scene> changeScene);
};