#pragma once
#include "Button.h"
#include "Vector2.h"
#include <memory>

class Image;
class PauseScene;

// �|�[�Y��ʂ́u�^�C�g���ɖ߂�v�{�^��
class ButtonReturnToTitle : public Button
{ 
private:
	int m_frameTimer;

	std::shared_ptr<Image> m_image;
	PauseScene& m_pauseSceneRef;

	void FocusedUpdate() override;
	void NormalUpdate() override;
public:
	ButtonReturnToTitle(Vector2 initPos, PauseScene& parent);
	~ButtonReturnToTitle();

	void OnFocused() override;
	void OnDisfocused() override;

	void OnPressed() override;

	void Draw() const override;
};

