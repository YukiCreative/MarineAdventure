#pragma once
#include "Scene.h"
#include <memory>

class ImageObject;
class Camera;

class SceneGameover : public Scene
{
private:
	std::shared_ptr<ImageObject> m_backGround;
public:
	SceneGameover();

	void Entry() override;
	void NormalUpdate() override;
	void Draw() const override;
};

