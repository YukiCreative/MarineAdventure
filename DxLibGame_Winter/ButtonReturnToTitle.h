#pragma once
#include "Button.h"
#include "Vector2.h"
#include <memory>

class Image;
class PauseScene;

// ポーズ画面の「タイトルに戻る」ボタン
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

