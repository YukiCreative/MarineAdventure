#pragma once
#include "Scene.h"
#include <memory>

class ScreenFade;
class BackGround;
class Camera;

class SceneGameClear : public Scene
{
private:
	ScreenFade& m_fade;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<BackGround> m_back;

	void NormalUpdate() override;
public:
	SceneGameClear();

	void Draw() const override;

	void Entry() override;
};

