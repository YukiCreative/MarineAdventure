#pragma once
#include "Scene.h"
#include <memory>

class BackGround;
class Camera;
class ScreenFade;
class ButtonSystem;

// ˆê”ÔÅ‰‚É•\¦‚³‚ê‚éƒV[ƒ“
class SceneTitle : public Scene
{
private:
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<BackGround> m_backGround;
	std::shared_ptr<ButtonSystem> m_buttonSystem;
public:
	SceneTitle();

	void Entry() override;
	void NormalUpdate() override;
	void Draw() const override;

	void GameStart();
};

