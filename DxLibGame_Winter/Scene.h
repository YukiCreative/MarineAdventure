#pragma once
#include <list>
#include <string>
#include <memory>

class ScreenFade;
class Camera;

class Scene
{
protected:
	using UpdateState_t = void (Scene::*)();
	UpdateState_t m_update;
	// フェードしたあと、遷移する次のシーン
	// すまん スコープの関係上メンバ変数になった
	std::string m_fadedNextScene;

	void SceneChangeUpdate();
	void SceneResumeUpdate();
	void SceneStackUpdate ();
	void SceneRemoveUpdate();

	// 12/25 フェードを義務化
	ScreenFade& m_fade;
	// 01/14 カメラを義務化
	std::shared_ptr<Camera> m_camera;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void NormalUpdate() = 0;
	// フェードアウトしてシーン遷移
	void SceneChangeWithFadeOut(const std::string& nextSceneId, const int& toralFrame = 60, const float& percent = 100.0f);
	void SceneResumeWithFadeOut(const std::string& nextSceneId, const int& toralFrame = 60, const float& percent = 100.0f);
	void SceneStackWithFadeOut (const std::string& nextSceneId, const int& toralFrame = 60, const float& percent = 100.0f);
	void SceneRemoveWithFadeOut(                                const int& toralFrame = 60, const float& percent = 100.0f);
public:
	Scene();
	/// <summary>
	/// 明示的にデストラクタをvirtualにしないといけないと聞いて
	/// </summary>
	virtual ~Scene() {}
	// SceneControllerが回す関数
	// 内部の状態にNormalとFadeがある
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() const = 0;

	// シーンに入った時にやりたいことを書く
	// これはポーズシーンから戻った時なども実行される
	virtual void Entry() = 0;
	// Entryの逆　シーンから離れるときに実行
	// いらないシーンもあるので、純粋にはしない
	virtual void Leave();

	std::shared_ptr<Camera> GetCamera() { return m_camera; }
};