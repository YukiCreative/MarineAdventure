#pragma once
#include <memory>
#include <list>

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

	using SceneList_t = std::list<std::shared_ptr<Scene>>;
	SceneList_t m_scenes;
	bool m_changedSceneInThisFrame;
public:
	static SceneController& GetInstance();

	// 一番上のシーンのみ実行される
	void Update();
	void Draw();

	// 今実行中のシーンを別のものに替える
	void ChangeScene(std::shared_ptr<Scene> changeScene);
	// シーンを重ねる
	void StackScene(std::shared_ptr<Scene> addScene);
	// 最後尾のシーンを削除
	void RemoveSceme();
};