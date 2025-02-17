#pragma once
#include "Button.h"
#include <memory>

class Image;

class ButtonQuitGame : public Button
{
private:
	void FocusedUpdate() override;
	void NormalUpdate()  override;

	std::shared_ptr<Image> m_image;
	int m_frameCount;
public:
	// �����ƋC�ɂȂ��Ă邯��
	// �Q�Ƃ̂����ł��̃N���X�ɂƂ��Ďv��ʒl�̕ω��Ƃ��͋N���Ȃ��̂���
	ButtonQuitGame(const Vector2& initPos);

	void OnFocused()    override;
	void OnDisfocused() override;
	void OnPressed()    override;

	void Draw() const override;
};

