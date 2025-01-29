#pragma once
#include <memory>
#include <list>
#include <unordered_map>
#include <string>

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

	using SceneFactory_t = std::shared_ptr<Scene> (*)();
	std::unordered_map<std::string, SceneFactory_t> m_factoryMap;

	int m_hitStopCount;
public:
	static SceneController& GetInstance();

	// 一番上のシーンのみ実行される
	void Update();
	void Draw();

	// 今実行中のシーンを別のものに替える
	void ChangeScene(std::string sceneId);
	// 一回展開しているシーンを全部片づけて新しいシーン一つだけにする
	void ResumeScene(std::string sceneId);
	// シーンを重ねる
	void StackScene(std::string addSceneId);
	// 最後尾のシーンを削除
	void RemoveSceme();

	// 今実行中のシーンを返す
	std::shared_ptr<Scene> CurrentScene() { return m_scenes.back(); }
	void HitStop(const int frame);
};