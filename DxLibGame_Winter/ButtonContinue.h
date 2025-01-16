#pragma once
#include "Button.h"
// ���̕Ӑ�Γ���邩����N���X�ɒu���Ă����̂ł�

class Image;

// �Q�[���I�[�o�[��ʂɐݒu����
class ButtonContinue : public Button
{
private:
	std::shared_ptr<Image> m_image;

	void FocusedUpdate() override;
	void NormalUpdate() override;
public:
	ButtonContinue(const Vector2& initPos);

	void Draw() const override;

	void OnFocused() override;
	void OnDisfocused() override;

	void OnPressed() override;
};

