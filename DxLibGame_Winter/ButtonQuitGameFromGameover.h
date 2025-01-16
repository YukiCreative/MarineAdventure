#pragma once
#include "Button.h"

class Image;

// ‚·‚Å‚Éì‚Á‚½ƒ{ƒ^ƒ“‚Æ–ğŠ„‚ª‚©‚Ô‚Á‚Ä‚é‚â‚Â‚ª‚ß‚ñ‚Ç‚­‚³‚·‚¬‚é
class ButtonQuitGameFromGameover : public Button
{
private:
	std::shared_ptr<Image> m_image;

	void FocusedUpdate() override;
	void NormalUpdate() override;
public:
	ButtonQuitGameFromGameover(const Vector2& initPos);

	void Draw() const override;

	void OnFocused() override;
	void OnDisfocused() override;

	void OnPressed() override;
};

