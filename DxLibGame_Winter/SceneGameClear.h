#pragma once
#include "Scene.h"
#include <memory>

class ScreenFade;
class ImageObject;
class Camera;

class SceneGameClear : public Scene
{
private:
	std::shared_ptr<ImageObject> m_back;

	void NormalUpdate() override;
public:
	void Init() override;

	void Draw() const override;

	void Entry() override;
};

