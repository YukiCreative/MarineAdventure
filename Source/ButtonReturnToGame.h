#pragma once
#include "Button.h"
#include <memory>

class Image;
class ScenePause;

class ButtonReturnToGame : public Button
{
private:
	int m_frameCount;

	std::shared_ptr<Image> m_image;
	ScenePause& m_pauseSceneRef;

	void FocusedUpdate() override;
	void NormalUpdate() override;

public:
	ButtonReturnToGame(Vector2 initPos, ScenePause& pauseScene);
	~ButtonReturnToGame();

	void OnFocused() override;
	void OnDisfocused() override;

	void OnPressed() override;

	void Draw() const override;
};

