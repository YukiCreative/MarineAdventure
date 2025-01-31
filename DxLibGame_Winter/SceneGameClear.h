#pragma once
#include "Scene.h"
#include <memory>

class ScreenFade;
class ImageObject;
class Camera;
class ButtonSystem;

class SceneGameClear : public Scene
{
private:
	std::shared_ptr<ImageObject> m_back;
	std::shared_ptr<ImageObject> m_clearText;
	std::shared_ptr<ButtonSystem> m_buttonSystem;

	void NormalUpdate() override;
public:
	void Init() override;

	void Draw() const override;

	void Entry() override;
};

