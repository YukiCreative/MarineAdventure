#pragma once
#include "Scene.h"
#include <memory>

class ImageObject;
class Camera;
class ButtonSystem;

class SceneGameover : public Scene
{
private:
	std::shared_ptr<ImageObject> m_backGround;
	std::shared_ptr<ButtonSystem> m_buttonController;

public:
	SceneGameover();

	void Entry() override;
	void NormalUpdate() override;
	void Draw() const override;

	// ƒ|[ƒY‚É‚à“¯‚¶ŠÖ”‚ ‚é‚Ì‚ª‚È‚ 
	void ReturnToTitle();
};

