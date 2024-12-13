#pragma once
#include "Scene.h"
#include <memory>

class BackGround;

class SceneGameover : public Scene
{
private:
	// îwåi
	std::shared_ptr<BackGround> m_gameoverBack;
public:
	SceneGameover();

	void Update() override;
	void Draw() const override;
};

