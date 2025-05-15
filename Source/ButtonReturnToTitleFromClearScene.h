#pragma once
#include "Button.h"
#include <memory>
#include "Image.h"

class ButtonReturnToTitleFromClearScene : public Button
{
private:
	std::shared_ptr<Image> m_image;
	int m_frameCount;
	int m_transparencyParam;

	void FocusedUpdate() override;
	void NormalUpdate() override;
public:
	ButtonReturnToTitleFromClearScene(const Vector2& initPos);

	void OnFocused() override;
	void OnDisfocused() override;
	void OnPressed() override;

	void Draw() const override;

	// “§–¾“x‚Ì•ÏX‚¾‚¯s‚¤
	void ChangeTransparency(const int param);
};

