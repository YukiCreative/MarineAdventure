#pragma once
#include "Button.h"

// ‚Ç‚±‚É‚à‘JˆÚ‚µ‚È‚¢ƒ{ƒ^ƒ“
class ButtonNoFocus : public Button
{
private:
	void FocusedUpdate() override {};
	void NormalUpdate() override {};
public:
	ButtonNoFocus() : Button(Vector2::Zero()) {}
	~ButtonNoFocus(){}

	void Draw() const override {}

	void OnPressed() override {};
};