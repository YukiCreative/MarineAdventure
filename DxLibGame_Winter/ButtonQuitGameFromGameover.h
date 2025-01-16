#pragma once
#include "Button.h"

class Image;

// ���łɍ�����{�^���Ɩ��������Ԃ��Ă����߂�ǂ���������
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

