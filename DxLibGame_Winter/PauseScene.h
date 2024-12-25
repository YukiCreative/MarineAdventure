#pragma once
#include "Scene.h"
#include <memory>

class BackGround;
class Camera;

// このクラスにさせたいこと
// オプションシーンへ
// タイトルに戻る
// 装飾用の画像
class PauseScene : public Scene
{
private:
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<BackGround> m_back;
public:
	PauseScene();

	void NormalUpdate() override;
	void Draw() const override;
};

