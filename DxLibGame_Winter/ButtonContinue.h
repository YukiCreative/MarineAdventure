#pragma once
#include "Button.h"
// この辺絶対入れるから基底クラスに置いていいのでわ

class Image;

// ゲームオーバー画面に設置する
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

