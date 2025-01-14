#pragma once
#include "Scene.h"
#include <memory>

class ImageObject;
class Camera;
class ButtonSystem;

// このクラスにさせたいこと
// オプションシーンへ
// タイトルに戻る
// 装飾用の画像
class ScenePause : public Scene
{
private:
	std::shared_ptr<ImageObject> m_back;
	std::shared_ptr<ButtonSystem> m_buttonSystem;
public:
	ScenePause();
	~ScenePause();

	void Entry() override;
	void NormalUpdate() override;
	void Draw() const override;

	void ReturnToTitle();
	void ReturnToGame();
};

