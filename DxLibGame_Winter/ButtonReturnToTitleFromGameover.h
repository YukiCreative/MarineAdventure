#pragma once
#include "Button.h"
#include <memory>

class Image;

// ƒNƒ‰ƒX–¼‚ª’·‚¢
class ButtonReturnToTitleFromGameover : public Button
{
private:
	void FocusedUpdate() override;
	void NormalUpdate() override;

	std::shared_ptr<Image> m_image;
public:
	ButtonReturnToTitleFromGameover(const Vector2& initPos);

	void Draw() const override;

	void OnFocused()    override;
	void OnDisfocused() override;
	void OnPressed()    override;
};

