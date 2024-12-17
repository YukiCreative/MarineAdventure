#pragma once
#include "Scene.h"
#include <memory>

class BackGround;
class Camera;
class ScreenFade;

// ˆê”ÔÅ‰‚É•\¦‚³‚ê‚éƒV[ƒ“
class SceneTitle : public Scene
{
private:
	ScreenFade& m_fade;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<BackGround> m_backGround;
public:
	SceneTitle();
	~SceneTitle();

	void Update() override;
	void Draw() const override;
};

