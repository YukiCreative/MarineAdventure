#pragma once
#include "Button.h"
#include <memory>

class Image;
class SceneTitle;

class ButtonGameStart : public Button
{
private:
	std::shared_ptr<Image> m_image;
	int m_frameCount;
	// ��������ă{�^�����ƂɌʂɐݒ肵�Ă����̂��낤���i��ɊJ�����x�I�Ɂj
	SceneTitle& m_titleRef;
public:
	ButtonGameStart(Vector2 initPos, SceneTitle& title);

	void NormalUpdate() override;
	void FocusedUpdate() override;

	void OnPressed() override;

	void Draw() const override;
};