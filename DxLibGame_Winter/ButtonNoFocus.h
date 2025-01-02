#pragma once
#include "Button.h"

// �ǂ��ɂ��J�ڂ��Ȃ��{�^��
class ButtonNoFocus : public Button
{
private:
	void FocusedUpdate() override {};
	void NormalUpdate() override {};
public:
	ButtonNoFocus() : Button(Vector2::Zero()) {}
	~ButtonNoFocus(){}

	void OnFocused() override {};
	void OnDisfocused() override {};

	void Draw() const override {}

	void OnPressed() override {};
};