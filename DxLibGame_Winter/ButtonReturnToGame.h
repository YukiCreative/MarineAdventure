#pragma once
#include "Button.h"
#include <memory>

class Image;
class PauseScene;

class ButtonReturnToGame : public Button
{
private:
	int m_frameCount;

	std::shared_ptr<Image> m_image;
	PauseScene& m_pauseSceneRef;

	void FocusedUpdate() override;
	void NormalUpdate() override;

public:
	ButtonReturnToGame(Vector2 initPos, PauseScene& pauseScene);

	void OnPressed() override;

	void Draw() const override;
};

