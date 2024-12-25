#pragma once
#include "Scene.h"
#include <memory>

class BackGround;
class Camera;

class SceneGameover : public Scene
{
private:
	std::shared_ptr<BackGround> m_backGround;
	std::shared_ptr<Camera> m_camera;
public:
	SceneGameover();

	void NormalUpdate() override;
	void Draw() const override;
};

