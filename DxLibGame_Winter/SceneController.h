#pragma once
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

	Scene& m_scene;
public:
	//static GetInstance();

	void Update();
	void Draw();

	void ChangeScene(Scene& changeScene);
};