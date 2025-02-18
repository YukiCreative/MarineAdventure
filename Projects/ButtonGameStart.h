#pragma once
#include "Button.h"
#include <memory>

class Image;
class SceneTitle;

class ButtonGameStart : public Button
{
private:
	std::shared_ptr<Image> m_image;
	int m_frameCount;

	SceneTitle& m_titleRef;

	void NormalUpdate() override;
	void FocusedUpdate() override;
public:
	ButtonGameStart(Vector2 initPos, SceneTitle& title);

	void OnFocused() override;
	void OnDisfocused() override;

	void OnPressed() override;

	void Draw() const override;
};