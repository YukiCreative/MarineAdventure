#pragma once
#include "Button.h"

// �ǂ��ɂ��J�ڂ��Ȃ��{�^��
class ButtonNoFocus : public Button
{
private:
	void ForcusedUpdate() override {};
	void NormalUpdate() override {};
public:
	ButtonNoFocus() : Button(Vector2::Zero()) {}

	void Draw() const override {}

	void Onpressed() override {};
};